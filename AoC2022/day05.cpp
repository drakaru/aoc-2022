#include "common/aoc.h"
#include <stack>

int main() {
	ScopedTimer const timer{"day05:total"};

	auto lines = input_lines("day05");

	ScopedTimer const timer2{"day05:noload"};

	size_t const stacks_stride = 4;
	size_t const stacks_offset = 1;
	size_t const stacks_n = 9;
	std::vector<std::stack<char>> stacks{stacks_n};

	size_t rows = 0;
	for (auto const &line: lines) {
		if (line[stacks_offset] == '1') {
			break;
		}
		rows++;
	}

	for (size_t line_idx = 1; line_idx <= rows; line_idx++) {
		for (size_t stack_idx = 0; stack_idx < stacks_n; stack_idx++) {
			char const c = lines[rows - line_idx][stacks_offset + stack_idx * stacks_stride];
			if (c != ' ') {
				stacks[stack_idx].push(c);
			}
		}
	}

	// copy stacks for p2
	std::vector<std::stack<char>> stacks2 = stacks;

	for (size_t line_idx = rows + 2; line_idx < lines.size(); line_idx++) {
		// hm...
		std::vector<uint16_t> line_words{};
		extract_into(lines[line_idx], line_words, ' ');

		uint16_t const count = line_words[0];
		uint16_t const source = line_words[1] - 1;
		uint16_t const dest = line_words[2] - 1;

		for (int x = 0; x < count; x++) {
			stacks[dest].push(stacks[source].top());
			stacks[source].pop();
		}

		std::stack<char> temp{};
		for (int x = 0; x < count; x++) {
			temp.push(stacks2[source].top());
			stacks2[source].pop();
		}
		while (!temp.empty()) {
			stacks2[dest].push(temp.top());
			temp.pop();
		}
	}

	std::cout << "p1: ";
	for (auto &stack: stacks) {
		std::putchar(stack.top());
	}
	std::cout << ", p2: ";
	for (auto &stack: stacks2) {
		std::putchar(stack.top());
	}
	std::cout << "\n";

	return 0;
}

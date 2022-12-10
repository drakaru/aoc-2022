#include "common/aoc.h"
#include <cmath>

void do_cycle(int64_t reg_x, uint64_t& cycle, uint64_t& tsig, uint64_t& interesting, uint64_t& cr)
{
	uint64_t const screen_width = 40;
	uint64_t const col = (cycle % screen_width) - 1;

	if (col >= (reg_x - 1) && col <= (reg_x + 1)) {
		std::putchar('#');
	} else {
		std::putchar('.');
	}

	if (cycle == interesting) {
		interesting += screen_width;
		tsig += reg_x * cycle;
	}

	if (cycle == cr) {
		cr += screen_width;
		std::putchar('\n');
	}

	cycle++;
}

int main()
{
	ScopedTimer const timer{"day10:total"};

	auto const lines = input_lines("day10");

	ScopedTimer const timer2{"day10:noload"};

	uint64_t cycle = 1;
	int64_t reg_x = 1;
	uint64_t interesting = 20;
	uint64_t cr = 40;
	uint64_t tsig = 0;

	for (auto const& line : lines) {
		if (line[0] == 'n') {
			do_cycle(reg_x, cycle, tsig, interesting, cr);
		} else {
			do_cycle(reg_x, cycle, tsig, interesting, cr);
			do_cycle(reg_x, cycle, tsig, interesting, cr);
			reg_x += std::stoi(line.substr(5));
		}
	}

	std::cout << "\nday10 p1: " << tsig << "\n";
}

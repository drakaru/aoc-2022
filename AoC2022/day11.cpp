#include "common/aoc.h"
#include <cmath>
#include <deque>

enum Operation {
	MUL,
	ADD
};

Operation to_op(char c) {
	return c == '*' ? MUL : ADD;
}

struct Monkey {
	uint64_t inspections = 0;
	std::deque<uint64_t> items{};
	size_t to_throw = 0;
	Operation op;
	uint64_t operand;
	uint16_t test;
	size_t true_monkey;
	size_t false_monkey;
};

void get_items(std::string const& line, Monkey& monkey){
	std::string line_vals = line.substr(line.find(':')+2);

	while (true) {
		auto pos = line_vals.find(',');
		if (pos == std::string::npos) {
			monkey.items.push_back(static_cast<uint64_t>(std::stoull(line_vals)));
			break;
		} else {
			auto cv = line_vals.substr(0, pos);
			monkey.items.push_back(static_cast<uint64_t>(std::stoull(cv)));
			line_vals = line_vals.substr(pos + 1);
		}
	}
}

void get_op(std::string const& line, Monkey& monkey){
	char const c = line[23];
	monkey.op = to_op(c);
}

void get_operand(std::string const& line, uint64_t& operand){
	// UINT64_MAX represents self, ie old * old or old + old
	auto const& val = line.substr(line.rfind(' ') + 1);
	auto res = std::from_chars(val.data(), val.data()+val.size(), operand);
	if(res.ec != std::errc{}) {
		operand = UINT64_MAX;
	}
}

void get_test(std::string const& line, Monkey& monkey){
	auto const& div = line.substr(line.rfind(' '));
	monkey.test = static_cast<uint16_t>(std::stoul(div));
}

void get_monkey(std::string const& line, size_t& monkey){
	auto const& div = line.substr(line.rfind(' '));
	monkey = static_cast<uint16_t>(std::stoul(div));
}

uint64_t divisor(std::vector<Monkey> const& monkeys) {
	uint64_t divisor = monkeys[0].test;

	for(size_t idx = 1; idx < monkeys.size(); idx++) {
		divisor *= monkeys[idx].test;
	}

	return divisor;
}

uint64_t get_answer(std::vector<Monkey>& monkeys) {
	auto cmp = [](Monkey& m1, Monkey& m2){ return m1.inspections > m2.inspections; };
	std::partial_sort(monkeys.begin(), monkeys.begin() + 2, monkeys.end(), cmp);
	return monkeys[0].inspections * monkeys[1].inspections;
}

uint64_t simulate(std::vector<Monkey> const& m, uint32_t rounds, bool p1) {
	std::vector<Monkey> monkeys = m;
	uint64_t d = divisor(monkeys);

	for (uint32_t round = 0; round < rounds; round++) {
		for (auto& monkey : monkeys) {
			while (!monkey.items.empty()) {
				uint64_t worry = monkey.items.front();
//				std::cout << " Monkey inspects an item with a worry level of "<< worry << ".\n";
				monkey.items.pop_front();
				monkey.inspections++;
				monkey.to_throw--;

				uint64_t const rhs = monkey.operand == UINT32_MAX ? worry : monkey.operand;
				if (monkey.op == Operation::MUL) {
					worry *= rhs;
//					std::cout << "  Worry level is multiplied by " << rhs << " to " << worry << ".\n";
				} else {
					worry += rhs;
//					std::cout << "  Worry level increases by " << rhs << " to " << worry << ".\n";
				}

				if (p1) {
					worry = static_cast<uint64_t>(std::floor(static_cast<double>(worry) / 3.0));
				} else {
					worry = worry % d;
				}

//				std::cout << "  Monkey gets bored with item. Worry level is divided by 3 to " << worry << ".\n";

				if (worry % monkey.test == 0) {
//					std::cout << "  Current worry level is divisible by " << monkey.test << ".\n";
//					std::cout << "  Item with worry level " << worry << " is thrown to monkey " << monkey.true_monkey << ".\n";
					monkeys[monkey.true_monkey].items.push_back(worry);
				} else {
//					std::cout << "  Current worry level is not divisible by " << monkey.test << ".\n";
//					std::cout << "  Item with worry level " << worry << " is thrown to monkey " << monkey.false_monkey << ".\n";
					monkeys[monkey.false_monkey].items.push_back(worry);
				}
			}
		}
	}

	return get_answer(monkeys);
}

int main()
{
	ScopedTimer const timer{"day11:total"};

	std::vector<Monkey> monkeys{};

	size_t const monkey_len = 6;
	auto const& lines = input_lines("day11");

	ScopedTimer const timer2{"day11:noload"};
	for (size_t start_idx = 0; start_idx < lines.size(); start_idx += monkey_len + 1)
	{
		Monkey monkey{};
		get_items(lines[start_idx+1], monkey);
		get_op(lines[start_idx+2], monkey);
		get_operand(lines[start_idx+2], monkey.operand);
		get_test(lines[start_idx+3], monkey);
		get_monkey(lines[start_idx+4], monkey.true_monkey);
		get_monkey(lines[start_idx+5], monkey.false_monkey);

		monkeys.push_back(monkey);
	}


	std::cout << "p1: " << simulate(monkeys, 20, true);

	ScopedTimer const timer3{"day11:p2"};
	std::cout << " p2: " << simulate(monkeys, 10000, false) << "\n";

}

#include "common/aoc.h"
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <array>

uint64_t part1(std::vector<std::string> const& rucksacks);
uint64_t part2(std::vector<std::string> const& rucksacks);

uint64_t priority(char c)
{
	uint64_t const lower_base = 1;
	uint64_t const upper_base = 27;
	return c >= 'a' && c <= 'z' ? static_cast<uint64_t>(c - 'a') + lower_base : static_cast<uint64_t>(c - 'A') + upper_base;
}

int main()
{
	ScopedTimer const timer{"day03:total"};

	auto rucksacks = input_lines("day03");

	auto p1 = part1(rucksacks);
	auto p2 = part2(rucksacks);

	std::cout << "p1: " << p1 << ", p2: " << p2 << "\n";

	return 0;
}

uint64_t part1(std::vector<std::string> const& rucksacks)
{
	ScopedTimer const timer{"day03:part1"};

	uint64_t total_priority = 0;

	for (auto const& rs: rucksacks)
	{
		auto const compartment_size = rs.size() / 2;
		std::string_view const left {rs.data(), compartment_size};
		std::string_view const right {&rs[compartment_size], compartment_size};

		for (auto const c : left)
		{
			if (right.contains(c))
			{
				total_priority += priority(c);
				break;
			}
		}
	}
	return total_priority;
}

/*uint64_t rs_group(std::string const& rs1, std::string const& rs2, std::string const& rs3)
{
	// explore using array for counter{}; ?
	std::unordered_map<char,int> counter{};

	{
		std::unordered_set<char> sack_set{};
		for (auto c : rs1) {
			sack_set.insert(c);
		}
		for (auto c : sack_set) {
			counter[c]++;
		}
	}

	{
		std::unordered_set<char> sack_set{};
		for (auto c : rs2) {
			sack_set.insert(c);
		}
		for (auto c : sack_set) {
			counter[c]++;
		}
	}

	{
		std::unordered_set<char> sack_set{};
		for (auto c : rs3) {
			sack_set.insert(c);
		}
		for (auto c : sack_set) {
			counter[c]++;
			if (counter[c] >= 3) {
				//std::cout << "group: \n " << rs1 << "\n " << rs2 << "\n " << rs3 << "\n common: " << c << "\n\n";
//				std::cout << "common: " << c << "\n";
				return priority(c);
			}
		}
	}

	return 0; // ... ah fuck
}

uint64_t part2(std::vector<std::string> const& rucksacks)
{
	ScopedTimer const timer{"day03:part2"};

	uint64_t total_priority = 0;

	for (size_t idx = 0; idx < rucksacks.size() - 2; idx += 3)
	{
		total_priority += rs_group(rucksacks[idx], rucksacks[idx+1], rucksacks[idx+2]);
	}
	return total_priority;
}*/

uint64_t part2(std::vector<std::string> const& rucksacks)
{
	ScopedTimer const timer{"day03:part2"};

	std::array<uint8_t, 'z' + 1> counter{};

	uint64_t total_priority = 0;

	for (size_t idx = 0; idx < rucksacks.size() - 2; idx += 3)
	{
		{
			std::unordered_set<char> sack_set{};
			for (auto const c : rucksacks[idx]) {
				sack_set.insert(c);
			}
			for (auto const c : sack_set) {
				counter[c]++;
			}
		}

		{
			std::unordered_set<char> sack_set{};
			for (auto const c : rucksacks[idx+1]) {
				sack_set.insert(c);
			}
			for (auto const c : sack_set) {
				counter[c]++;
			}
		}

		{
			std::unordered_set<char> sack_set{};
			for (auto const c : rucksacks[idx+2]) {
				sack_set.insert(c);
			}
			for (auto const c : sack_set) {
				counter[c]++;
				if (counter[c] >= 3) {
					// std::cout << "group: \n " << rucksacks[idx] << "\n " << rucksacks[idx+1] << "\n " << rucksacks[idx+2] << "\n common: " << c << "\n\n";
					// std::cout << "common: " << c << "\n";
					total_priority += priority(c);
					break;
				}
			}
		}

		std::memset(&counter['A'], 0, 'z' - 'A' + 1);
	}

	return total_priority;
}

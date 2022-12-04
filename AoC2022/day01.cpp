#include "common/aoc.h"
#include <algorithm>

uint64_t part1(std::vector<uint64_t> const&);
uint64_t part2(std::vector<uint64_t> const&);

int main()
{
	ScopedTimer const timer1{"day01:total"};

	std::vector<uint64_t> elves{};
	uint64_t cals = 0;

	for (auto const& line : input_lines("day01"))
	{
		if (!line.empty())
		{
			cals += std::stoull(line);
		} else {
			elves.push_back(cals);
			cals = 0;
		}
	}

	ScopedTimer const timer2{"day01:sansload"};
	std::partial_sort(elves.begin(), elves.begin() + 3, elves.end(), std::greater{});
	std::cout << "p1: " << part1(elves) << "\n";
	std::cout << "p2: " << part2(elves) << "\n";

}

uint64_t part1(std::vector<uint64_t> const& elves)
{
	ScopedTimer const timer1{"day01:part1"};
	//return *std::max_element(elves.cbegin(), elves.cend());
	return elves[0];
}

uint64_t part2(std::vector<uint64_t> const& elves)
{
	ScopedTimer const timer1{"day01:part2"};

	/*std::vector<uint64_t> p2_elves = elves;

	std::partial_sort(p2_elves.begin(), p2_elves.begin() + 3, p2_elves.end(), std::greater{});

	return p2_elves[0] + p2_elves[1] + p2_elves[2];*/

	return elves[0] + elves[1] + elves[2];
}

#include "common/aoc.h"
#include <map>

uint64_t part1(std::vector<std::string> const& games);
uint64_t part2(std::vector<std::string> const& games);

using game_table = std::map<char,std::string>;

std::map<char,int> const hand_scores{
		{'X', 1},
		{'Y', 2},
		{'Z', 3},
};

int main()
{
	ScopedTimer const timer1{"day02:total"};
	auto games = input_lines("day02");

	ScopedTimer const timer2{"day02:sansload"};
	auto p1 = part1(games);
	auto p2 = part2(games);
	std::cout << "p1: " << p1 << "\n";
	std::cout << "p2: " << p2 << "\n";
}

uint64_t part1(std::vector<std::string> const& games)
{
	ScopedTimer const timer1{"day02:part1"};
	int tot = 0;

	const game_table table {
			{'X', "BAC"},
			{'Y', "CBA"},
			{'Z', "ACB"},
	};

	for (std::string const& line : games)
	{
		char const opp = line[0];
		char const me = line[2];
		int const round_score = static_cast<int>(table.at(me).find(opp) * 3);
		tot += round_score + hand_scores.at(me);
	}

	return tot;
}

uint64_t part2(std::vector<std::string> const& games)
{
	ScopedTimer const timer1{"day02:part2"};

	const std::map<char,int> strat_scores{
			{'X', 0},
			{'Y', 3},
			{'Z', 6},
	};

	const game_table table {
			{'A', "ZXY"},
			{'B', "XYZ"},
			{'C', "YZX"},
	};

	int tot = 0;

	for (std::string const& line : games)
	{
		char const opp = line[0];
		char const me = line[2];

		auto strat_str = table.at(opp);
		char const my_play = strat_str[hand_scores.at(me)-1];

		int const hand_score = hand_scores.at(my_play);
		int const round_score = strat_scores.at(me);

		tot += hand_score + round_score;

	}

	return tot;
}

#include "common/aoc.h"
#include <unordered_set>

size_t part1(std::vector<std::string> const& lines);
size_t part2(std::vector<std::string> const& lines);

using pos_t = std::pair<int16_t, int16_t>;

namespace std {
	template<>
	struct hash<pos_t> {
		inline size_t operator()(const pos_t &v) const {

			return (static_cast<size_t>(v.first) << 16) + static_cast<size_t>(v.second);
		}
	};
}

int main()
{
	ScopedTimer const timer{"day09:total"};

	auto const lines = input_lines("day09");

	ScopedTimer const timer2{"day09:noload"};

	auto p1 = part1(lines);
	auto p2 = part2(lines);

	std::cout << "day09 p1: " << p1 << ", p2: " << p2 << "\n";

}

size_t part1(std::vector<std::string> const& lines){
	ScopedTimer const timer{"day09:p1"};

	std::unordered_set<pos_t> visited{};
	pos_t head{};
	pos_t tail{};
	visited.insert(tail);

	for (auto const& line : lines)
	{
		auto const dist = std::stoul(line.substr(2, line.size()-2));

		for (unsigned x = 0; x < dist; ++x)
		{
			switch (line[0]) {
				case 'L':
					head.first--;
					break;
				case 'R':
					head.first++;
					break;
				case 'U':
					head.second++;
					break;
				case 'D':
					head.second--;
					break;
			}

			if(std::abs(head.first - tail.first) > 1 || std::abs(head.second - tail.second) > 1) {
				tail.first += head.first > tail.first ? 1 : head.first == tail.first ? 0 : -1;
				tail.second += head.second > tail.second ? 1 : head.second == tail.second ? 0 : -1;

				visited.insert(tail);
			}
		}
	}
	return visited.size();
}

size_t part2(std::vector<std::string> const& lines){
	ScopedTimer const timer{"day09:p2"};

	std::unordered_set<pos_t> visited{};
	std::array<pos_t,10> knots{};

	pos_t& head = knots.front();
	pos_t const& tail = knots.back();

	visited.insert(tail);

	for (auto const& line : lines)
	{
		auto const dist = std::stoul(line.substr(2, line.size()-2));

		for (unsigned x = 0; x < dist; ++x)
		{
			switch (line[0]) {
				case 'L':
					head.first--;
					break;
				case 'R':
					head.first++;
					break;
				case 'U':
					head.second++;
					break;
				case 'D':
					head.second--;
					break;
			}

			for (size_t idx = 1; idx < knots.size(); idx++)
			{
				pos_t const& k1 = knots[idx -1];
				pos_t& k2 = knots[idx];

				if(std::abs(k1.first - k2.first) > 1 || std::abs(k1.second - k2.second) > 1) {
					k2.first += k1.first > k2.first ? 1 : k1.first == k2.first ? 0 : -1;
					k2.second += k1.second > k2.second ? 1 : k1.second == k2.second ? 0 : -1;
				}

			}

			visited.insert(tail);
		}
	}

	return visited.size();
}

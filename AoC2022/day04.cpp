#include "common/aoc.h"

using ranges = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;

ranges parse(std::string const& line) {
	auto t1 = line.find('-');
	auto t2 = line.find(',', t1);
	auto t3 = line.find('-', t2);

	auto ll = std::string_view(line.begin(), line.begin() + t1);
	auto lu = std::string_view(line.begin() + t1 + 1, line.begin() + t2);

	auto rl = std::string_view(line.begin() + t2 + 1, line.begin() + t3);
	auto ru = std::string_view(line.begin() + t3 + 1, line.end());

	uint8_t a{}, b{}, c{}, d{};
	std::from_chars(ll.data(), ll.data() + ll.size(), a);
	std::from_chars(lu.data(), lu.data() + lu.size(), b);
	std::from_chars(rl.data(), rl.data() + rl.size(), c);
	std::from_chars(ru.data(), ru.data() + ru.size(), d);
	return {a, b, c, d};
}

int main() {
	ScopedTimer const timer{"day04:total"};

	uint16_t p1 = 0;
	uint16_t p2 = 0;

	ScopedTimer const timer2{"day04:sansload"};

	for (auto const &line: input_lines("day04")) {
		auto [l1, l2, r1, r2] = parse(line);

		if ((l1 <= r1 && l2 >= r2) || (r1 <= l1 && r2 >= l2)) {
			p1++;
		}
		if ((l1 <= r1 && l2 >= r1) || (l1 <= r2 && l2 >= r2) || (r1 <= l1 && r2 >= l1) || (r1 <= l2 && r2 >= l2)) {
			p2++;
		}
	}

	std::cout << "p1: " << p1 << ", p2: " << p2 << "\n";
}

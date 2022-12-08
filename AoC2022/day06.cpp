#include "common/aoc.h"
#include <deque>
#include <array>

struct counter_t {
	std::deque<char> queue{};
	std::array<uint8_t, 26> counts{};
	uint8_t unique = 0;
};

void find(counter_t& counter, auto &source, uint8_t threshold) {
	while (true) {
		auto current = *source - 'a';
		if (counter.counts[current] == 0) {
			counter.unique++;
		}
		counter.counts[current]++;
		counter.queue.push_front(*source);

		if (counter.queue.size() > threshold) {
			auto remove = counter.queue.back() - 'a';
			counter.counts[remove]--;
			if (counter.counts[remove] == 0) {
				counter.unique--;
			}
			counter.queue.pop_back();

		}

		source++;

		if (counter.unique >= threshold) {
			break;
		}
	}
}

int main() {
	std::vector<char> const stream = inputAsCharVector("day06");
	auto iter = stream.cbegin();
	counter_t counter{};

	find(counter, iter, 4);
	auto p1 = std::distance(stream.cbegin(), iter);

	find(counter, iter, 14);
	auto p2 = std::distance(stream.cbegin(), iter);

	std::cout << "p1: " << p1 << ", p2: " << p2 << "\n";
}

// ^^ faster rewrite, original vv

/*
int main()
{
	ScopedTimer const timer{"day06:total"};

	auto input_stream = get_input("day06");

	ScopedTimer const timer2{"day06:totalish"};
	std::deque<char> marker{};

	char c{};
	size_t p1 = 4;
	for (int x = 0; x < 4; x++)
	{
		input_stream >> c;
		marker.push_front(c);
	}

	while (true)
	{
		std::unordered_set<char> set{marker.cbegin(), marker.cend()};
		if (set.size() == marker.size()) {
			break;
		}
		input_stream >> c;
		marker.push_front(c);
		marker.pop_back();
		p1++;
	}

	size_t p2 = p1 + 10;
	for (int x = 0; x < 10; x++)
	{
		input_stream >> c;
		marker.push_front(c);
	}

	while (true)
	{
		std::unordered_set<char> set{marker.cbegin(), marker.cend()};
		if (set.size() == marker.size()) {
			break;
		}
		input_stream >> c;
		marker.push_front(c);
		marker.pop_back();
		p2++;
	}

	std::cout << "p1: " << p1 << ", p2: " << p2 << "\n";

	return 0;
}
*/
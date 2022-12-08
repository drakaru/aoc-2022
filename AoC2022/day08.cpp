#include "common/aoc.h"

struct Grid {
	std::vector<std::string> lines{};
	size_t width{};
	size_t height{};
};

bool visible(Grid const& grid, size_t const x, size_t const y) {
	char const value = grid.lines[y][x];
	if (!value) { return false; }

	char max_left = 0;
	for (size_t cx = 0; cx < x; cx++) {
		max_left = std::max(max_left, grid.lines[y][cx]);
	}
	if (max_left < value) { return true; }

	char max_right = 0;
	for (size_t cx = x+1; cx < grid.width; cx++) {
		max_right = std::max(max_right, grid.lines[y][cx]);
	}
	if (max_right < value) { return true; }

	char max_above = 0;
	for (size_t cy = 0; cy < y; cy++) {
		max_above = std::max(max_above, grid.lines[cy][x]);
	}
	if (max_above < value) { return true; }

	char max_below = 0;
	for (size_t cy = y+1; cy < grid.height; cy++) {
		max_below = std::max(max_below, grid.lines[cy][x]);
	}
	if (max_below < value) { return true; }

	return false;
}

size_t scene(Grid const& grid, size_t const x, size_t const y) {
	char const value = grid.lines[y][x];
	if (!value) { return false; }

	size_t dist_left = 0;
	for (size_t cx = x-1; cx < grid.width; cx--) { // unsigned abuse
		dist_left++;
		if (grid.lines[y][cx] >= value) { break; }
	}

	size_t dist_right = 0;
	for (size_t cx = x+1; cx < grid.width; cx++) {
		dist_right++;
		if (grid.lines[y][cx] >= value) { break; }
	}

	size_t dist_above = 0;
	for (size_t cy = y-1; cy < grid.height; cy--) { // unsigned abuse
		dist_above++;
		if (grid.lines[cy][x] >= value) { break; }
	}

	size_t dist_below = 0;
	for (size_t cy = y+1; cy < grid.height; cy++) {
		dist_below++;
		if (grid.lines[cy][x] >= value) { break; }
	}

	return dist_left * dist_right * dist_above * dist_below;
}

int main()
{
	ScopedTimer const timer{"day08:total"};

	Grid grid{};
	grid.lines = input_lines("day08");

	ScopedTimer const timer2{"day08:sansload"};

	grid.width = grid.lines[0].size();
	grid.height = grid.lines.size();

	// visible edges, each side - duplicated 4 corners
	uint64_t p1 = grid.width * 2 + grid.height * 2 - 4;
	uint64_t p2 = 0;

	for (size_t y = 1; y < grid.height - 1; y++)
	{
		for (size_t x = 1; x < grid.width - 1; x++)
		{
			if(visible(grid, x, y)) {
				p1++;
			}
			p2 = std::max(p2, scene(grid, x, y));
		}
	}

	std::cout << "p1: " << p1 << ", p2: " << p2 << "\n";
}

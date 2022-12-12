#include "common/aoc.h"
#include <deque>
#include <unordered_set>

struct uivec2 {
	uint16_t x;
	uint16_t y;

	bool operator==(const uivec2& other) const {
		return x == other.x && y == other.y;
	}
};

namespace std {
	template<>
	struct hash<uivec2> {
		inline size_t operator()(const uivec2 &v) const {
			return (static_cast<size_t>(v.x) << 16) + static_cast<size_t>(v.y);
		}
	};
}

std::vector<uivec2> neighbours(uivec2 const& p, size_t width, size_t height, std::unordered_set<uivec2> const& visited) {
	std::vector<uivec2> n{};

	if (p.x > 0) {
		uivec2 const pn{static_cast<uint16_t>(p.x - 1), static_cast<uint16_t>(p.y)};
		if (!visited.contains(pn)) {
			n.push_back(pn);
		}
	}

	if (p.x < width - 1) {
		uivec2 const pn{static_cast<uint16_t>(p.x + 1), static_cast<uint16_t>(p.y)};
		if (!visited.contains(pn)) {
			n.push_back(pn);
		}
	}

	if (p.y > 0) {
		uivec2 const pn{static_cast<uint16_t>(p.x), static_cast<uint16_t>(p.y - 1)};
		if (!visited.contains(pn)) {
			n.push_back(pn);
		}
	}
	if (p.y < height - 1) {
		uivec2 const pn{static_cast<uint16_t>(p.x), static_cast<uint16_t>(p.y + 1)};
		if (!visited.contains(pn)) {
			n.push_back(pn);
		}
	}

	return n;

	uint16_t min_x = p.x > 0 ? p.x -1 : p.x;
	uint16_t min_y = p.y > 0 ? p.y -1 : p.y;

	uint16_t max_x = p.x < width - 1 ? p.x + 1 : p.x;
	uint16_t max_y = p.y < height - 1 ? p.y + 1 : p.y;


	for (uint16_t y = min_y; y <= max_y; ++y) {
		for (uint16_t x = min_x; x <= max_x; ++x) {
			if (x == p.x && y == p.y) { continue; }
			n.push_back({x,y});
		}
	}

	return n;
}

char elevation_at(std::vector<char> const& map, size_t width, uivec2 const& p) {
	char elev = map[width * p.y + p.x];
	if (elev == 'S') {
		elev = 'a';
	} else if (elev == 'E') {
		elev = 'z';
	}
	return elev;
}

uint16_t distance(std::vector<char> const& elevation, size_t width, size_t height, uivec2 const& s, uivec2 const& e) {
	std::unordered_set<uivec2> visited{};
	std::unordered_set<uivec2> to_visit{};
	std::unordered_set<uivec2> to_visit_next{};
	to_visit.insert(s);

	uint16_t dist = 0;
	while (true) {
		dist++;
		for (uivec2 const& visiting : to_visit) {
			visited.insert(visiting);

			char const ve = elevation_at(elevation, width, visiting); //elevation[width * visiting.y + visiting.x];

			for (uivec2 const& neighbour : neighbours(visiting, width, height, visited)) {
				char const ne = elevation_at(elevation, width, neighbour);
				char const ed = ne - ve;
				if (ed <= 1) {
//					if (!visited.contains(neighbour)){
					to_visit_next.insert(neighbour);
					if (neighbour == e) {
						break;
					}
//					}
				}
			}
		}

		if (to_visit_next.contains(e)) {
			break;
		}

		if (to_visit_next.empty()) {
			char max_elevation = 0;
			for (uivec2 const& visiting : visited) {
				max_elevation = std::max(max_elevation, elevation_at(elevation, width, visiting));
			}
			std::cout << "stuck at " << dist << " steps, max elevation found: " << max_elevation << "\n";
			break;
		}

		to_visit = to_visit_next;
		to_visit_next.clear();
	}

	return dist;
}


uint16_t distance2(std::vector<char> const& elevation, size_t width, size_t height, uivec2 const& s) {
	std::unordered_set<uivec2> visited{};
	std::unordered_set<uivec2> to_visit{};
	std::unordered_set<uivec2> to_visit_next{};
	to_visit.insert(s);

	uint16_t dist = 0;
	while (true) {
		dist++;
		for (uivec2 const& visiting : to_visit) {
			visited.insert(visiting);

			char const ve = elevation_at(elevation, width, visiting); //elevation[width * visiting.y + visiting.x];

			for (uivec2 const& neighbour : neighbours(visiting, width, height, visited)) {
				char const ne = elevation_at(elevation, width, neighbour);
				char const ed = ne - ve;
				if (ed >= -1) {
					to_visit_next.insert(neighbour);
					if (ne == 'a') {
						return dist;
					}
				}
			}
		}

		if (to_visit_next.empty()) {
			char max_elevation = 0;
			for (uivec2 const& visiting : visited) {
				max_elevation = std::max(max_elevation, elevation_at(elevation, width, visiting));
			}
			std::cout << "stuck at " << dist << " steps, max elevation found: " << max_elevation << "\n";
			break;
		}

		to_visit = to_visit_next;
		to_visit_next.clear();
	}

	return dist;
}

int main()
{
	ScopedTimer const timer{"day12:total"};
	auto const& lines = input_lines("day12");
	size_t const width = lines[0].size();
	size_t const height = lines.size();

	ScopedTimer const timer2{"day12:noload"};

	std::vector<char> elevation(width * height);

	uivec2 s{};
	uivec2 e{};

	size_t y = 0;
	for (auto const& line : lines) {
		size_t x = 0;
		for (auto const& c : line) {
			elevation[width * y + x] = c;
			if (c == 'S') {
				s.x = static_cast<uint16_t>(x);
				s.y = static_cast<uint16_t>(y);
			} else if (c == 'E') {
				e.x = static_cast<uint16_t>(x);
				e.y = static_cast<uint16_t>(y);
			}
			x++;
		}
		y++;
	}

	uint16_t const p1 = distance(elevation, width, height, s, e);
	uint16_t const p2 = distance2(elevation, width, height, e);

	std::cout << "p1: " << p1 << " p2: " << p2 << "\n";

}

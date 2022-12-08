#include "common/aoc.h"

struct dir
{
	size_t size = 0;
	dir* parent = nullptr;
};

int main()
{
	ScopedTimer const timer{"day07:total"};

	size_t p1 = 0;
	size_t p2 = SIZE_MAX;

	std::vector<dir> all_dirs{};
	// nasty hack to avoid vector resizing
	// which would invalidate the parent ptrs :)
	all_dirs.reserve(256);
	all_dirs.push_back({});
	dir const& root_dir = all_dirs[0];
	dir* working_dir = &all_dirs[0];

	auto terminal_log = input_lines("day07");

	ScopedTimer const timer2{"day07:sansload"};

	for (auto const& line : terminal_log)
	{
		bool is_command = line.starts_with('$');
		if (is_command) {
			if (line[2] == 'l') {
				// skip ls
				continue;
			}
			else {
				// must be cd
				// don't actually care about the name, the input never back tracks.
				// just add a new child to working_dir and switch to it.
				// unless it is cd .. and we take the size of working_dir and add it to the parent.
				std::string_view const target {line.begin()+5, line.end()};
				if (line[5] == '/') {
					// only appears at beginning of input, we're already at root
					continue;
				}
				else if (target == "..") {
					size_t const temp_size = working_dir->size;
					working_dir = working_dir->parent;
					working_dir-> size += temp_size;
				} else {
					dir new_dir{};
					new_dir.parent = working_dir;
					all_dirs.push_back(new_dir);
					working_dir = &all_dirs.at(all_dirs.size()-1);
				}

			}
		} else {
			// directory listing...
			// ignore dirs, don't care.
			if (line.starts_with('d')) {
				continue;
			}

			auto const idx = line.find(' ');
			auto const fss = line.substr(0, idx);
			size_t file_size = std::stoull(fss);

			working_dir->size += file_size;

			// std::cout << "found file of size: " << file_size << " in line :" << line << "\n";
		}
	}

	// input does not backtrack to root
	while (working_dir != &all_dirs[0]) {
		working_dir->parent->size += working_dir->size;
		working_dir = working_dir->parent;
	}

	size_t const fs_total = 70000000;
	size_t const fs_required = 30000000;
	size_t const fs_available = fs_total - root_dir.size;
	size_t const threshold = fs_required - fs_available;

	for (auto const dir : all_dirs)
	{
		if (dir.size < 100000) {
			p1 += dir.size;
		} else if (dir.size >= threshold && dir.size < p2) {
			p2 = dir.size;
		}
	}

	std::cout << "p1: " << p1 << ", p2: " << p2 << "\n";

	return 0;
}

#include "common/aoc.h"

struct dir
{
	size_t size = 0;
	// probably would have been better to use a stack<dir*> as we only need them as we backtrack
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

	size_t const cd_offset = 5;

	for (auto const& line : terminal_log)
	{
		// is command
		if (line[0] == '$') {
			// skip ls
			if (line[2] == 'l') { continue; }
			// must be cd
			// only appears at beginning of input when we're already at root
			if (line[cd_offset] == '/') { continue; }

			// don't actually care about the name, the input never back tracks.
			// unless it's .. then we add the size of working_dir to its parent.
			// otherwise add a new dir with working_dir as parent and switch to it.
			std::string_view const target {line.begin() + cd_offset, line.end()};
			if (target == "..") {
				working_dir->parent->size += working_dir->size;
				working_dir = working_dir->parent;
			} else {
				dir new_dir{};
				new_dir.parent = working_dir;
				all_dirs.push_back(new_dir);
				working_dir = &all_dirs.at(all_dirs.size()-1);
			}

		} else {
			// directory listing...
			// ignore dirs, don't care.
			if (line.starts_with('d')) {
				continue;
			}

			auto const idx = line.find(' ');
			auto const fss = line.substr(0, idx);
			size_t const file_size = std::stoull(fss);

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
	size_t const p1_threshold = 100000;
	size_t const p2_threshold = fs_required - fs_available;

	for (auto const dir : all_dirs)
	{
		if (dir.size < p1_threshold) {
			p1 += dir.size;
		} else if (dir.size >= p2_threshold && dir.size < p2) {
			p2 = dir.size;
		}
	}

	std::cout << "p1: " << p1 << ", p2: " << p2 << "\n";

	return 0;
}

#include "aoc_time.h"
#include <iostream>

ScopedTimer::ScopedTimer(std::string const& name)
{
	this->name = name;
	start = std::chrono::high_resolution_clock::now();
}

ScopedTimer::~ScopedTimer()
{
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << name << " elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed_seconds).count() << " microseconds\n";
};

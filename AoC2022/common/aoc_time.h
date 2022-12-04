#pragma once

#include <chrono>
#include <string>

#define AOC_TIMER(name) ScopedTimer const time##name{#name}

class ScopedTimer
{
	std::string name;
	std::chrono::high_resolution_clock::time_point start;
public:
	explicit ScopedTimer(std::string const& name);
	~ScopedTimer();
};
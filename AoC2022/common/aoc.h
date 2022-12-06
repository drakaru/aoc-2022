#pragma once

#include <iostream>
#include <fstream>
#include <functional>
#include <charconv>
#include <cstdint>
#include <string>
#include <sstream>
#include <vector>

#include "aoc_time.h"


std::string input_path(std::string const& day)
{
	char buf[256];
	sprintf(buf, "%s.txt", day.c_str());
	return std::string{buf};
}

std::ifstream get_input(std::string const& day)
{
	char buf[256];
	sprintf(buf, "%s.txt", day.c_str());
	return std::ifstream(std::string(buf));
}

std::vector<char> inputAsCharVector(std::string const& day) {
	std::string path = input_path(day);
	std::ifstream file(path, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	auto fileSize = file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}



void for_each_line(std::ifstream&& f, std::function<void(std::string const& line)> const& fun)
{
	std::string line;
	while (std::getline(f, line))
	{
		fun(line);
	}
}

std::vector<std::string> input_lines(std::string const& day)
{
	auto f = get_input(day);
	std::vector<std::string> lines{};
	std::string line;
	while (std::getline(f, line))
	{
		lines.push_back(line);
	}
	return lines;
}

template<typename T>
std::vector<T> input_lines_as(std::string const& day)
{
	auto f = get_input(day);
	std::vector<T> lines{};
	std::string line;
	while (std::getline(f, line))
	{
		T n;
		std::from_chars(line.data(), line.data() + line.size(), n);
		lines.push_back(n);
	}
	return lines;
}


template<typename T>
void extract_into(std::string const& csv, std::vector<T>& vec, char delim=',')
{
	std::stringstream source(csv);
	std::string item;
	while (getline(source, item, delim)) {
		T n;
		auto res = std::from_chars(item.data(), item.data() + item.size(), n);
		if(res.ec == std::errc{})
		{
			vec.push_back(n);
		}
	}
}
#include "aoc.hpp"

MapArray read_input(const std::string& file_name)
{
	std::vector<std::string> input;
	MapArray result = {};
	std::ifstream file(file_name);

	if (!file.is_open())
	{
		std::cerr << "Could not open the file: " << file_name << std::endl;
		abort();
		return {};
	}

	std::string line;
	while (std::getline(file, line))
	{
		Line lineData = {};
		for(auto& c : line)
		{
			lineData.push_back(c);
		}
		result.push_back(lineData);
	}
	return result;
}


char try_get(MapArray const& array, long x, long y)
{
	if (y < 0 || y >= static_cast<long>(array.size()))
	{
		return ' ';
	}

	if (x < 0 || x >= static_cast<long>(array[y].size()))
	{
		return ' ';
	}

	return array[y][x];
}

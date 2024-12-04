
#include <iostream>
#include <fstream>
#include <vector>
#include "aoc.hpp"



static bool has_word(MapArray const& array, int x, int y, int offx, int offy)
{
	// checking for XMAS
	if (try_get(array, x,y) != 'X')
		return false;

	if (try_get(array, x+offx,y+offy) != 'M')
		return false;

	if (try_get(array, x+2*offx,y+2*offy) != 'A')
		return false;

	if (try_get(array, x+3*offx,y+3*offy) != 'S')
		return false;

	return true;
}

static int word_count(MapArray const& array, int x, int y)
{
	if(try_get(array, x, y) != 'X')
	{
		return 0;
	}

	int acc = 0;

	for(int sx = -1; sx < 2; sx++)
	{
		for(int sy = -1; sy < 2; sy++)
		{
			if (sx == 0 && sy == 0)
				continue;

			if (has_word(array, x, y, sx, sy))
			{
				acc++;
			}
		}
	}
	return acc;
	
}
int first_solution(MapArray const& input)
{
	for(int y = 0; y < static_cast<int>(input.size()); y++)
	{
		for(int x = 0; x < static_cast<int>(input[y].size()); x++)
		{
			std::cout << input[y][x];
		}
		std::cout << std::endl;
	}

	int acc_word_count = 0;

	for(int y = 0; y < static_cast<int>(input.size()); y++)
	{
		for(int x = 0; x < static_cast<int>(input[y].size()); x++)
		{
			acc_word_count += word_count(input, x, y);
		}
	}
	
	std::cout << "(first solution) Final word count: " << acc_word_count << std::endl;
	return acc_word_count;
}

#pragma once 


#include <iostream>
#include <fstream>
#include <vector>


using Line = std::vector<char>;
using MapArray = std::vector<Line>;

MapArray read_input(const std::string& file_name);

char try_get(MapArray const& array, long x, long y);

int first_solution(MapArray const& input);
int second_solution(MapArray const& input);

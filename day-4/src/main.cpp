#include "aoc.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    MapArray input = read_input("input.txt");

    first_solution(input);
    second_solution(input);

    return 0;

}
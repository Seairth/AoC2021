#include <stdio.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;

#define INPUT_FILENAME "../input/day06.txt"
#define REGULAR_CYCLE 6
#define INITIAL_CYCLE REGULAR_CYCLE + 2

static uint64_t solve(int days)
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    string input;
    fs >> input;

    fs.close();

    replace(input.begin(), input.end(), ',', ' ');

    istringstream cycles(input);
    int cycle;
    uint64_t fish[INITIAL_CYCLE + 1] = {};

    while (cycles >> cycle) fish[cycle]++;

    for (cycle = 0; cycle < days; cycle++)
    {
        auto new_fish = fish[0];

        for(auto i = 0; i < (INITIAL_CYCLE); i++) fish[i] = fish[i+1];
        fish[REGULAR_CYCLE] += new_fish;
        fish[INITIAL_CYCLE] = new_fish;
    }

    uint64_t answer = 0;

    for (auto size: fish) answer += size;

    return answer;
}

static uint64_t puzzle1()
{
    return solve(80);
}

static uint64_t puzzle2()
{
    return solve(256);
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 6\nA: %lu\nB: %lu\n", answer1, answer2);
}

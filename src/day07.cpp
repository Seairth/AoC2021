#include <stdio.h>
#include <string>
#include <fstream>
#include <functional>
#include <map>
#include <math.h>

using namespace std;

#define INPUT_FILENAME "../input/day07.txt"

template<typename Functor>
static uint64_t solve(Functor fuelcost)
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    int position = 0, min_position = 10000, max_position = 0;
    map<int, int> crabs = {};

    while (fs >> position)
    {
        if (crabs.find(position) == crabs.end()) crabs[position] = 0;
        crabs[position]++;

        if (position < min_position) min_position = position;
        if (position > max_position) max_position = position;
    }

    fs.close();


    uint64_t answer = 0xFFFFFFFFFFFFFFFF;

    for (position = min_position; position <= max_position; position++)
    {
        uint64_t sum = 0;

        for (auto crab = crabs.begin(); crab != crabs.end(); crab++)
        {
            sum += crab->second * fuelcost(abs(position - crab->first));
        }

        if (sum < answer) answer = sum;
    }

    return answer;
}

static uint64_t puzzle1()
{
    return solve([](int distance) { return distance; });
}

static uint64_t puzzle2()
{
    auto fuelcost = [](int distance) {
        int total = 0;
        for (auto i = 0; i <= distance; i++ ) total+=i;
        return total;
    };

    return solve(fuelcost);
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 7\nA: %lu\nB: %lu\n", answer1, answer2);
}

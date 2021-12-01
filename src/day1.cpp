#include <stdio.h>
#include <fstream>

using namespace std;

static int day1a()
{
    ifstream fs("../input/day1.txt");

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    int depth;
    auto last_depth = 0;
    auto increases = -1; // to compensate for no previous depth note

    while (fs >> depth)
    {
        if (depth > last_depth)
        {
            increases++;
        }

        last_depth = depth;
    }

    fs.close();

    return increases;
}

static int day1b()
{
    ifstream fs("../input/day1.txt");

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    int depths[4];
    auto increases = 0;

    fs >> depths[0] >> depths[1] >> depths[2];

    while(!fs.eof())
    {
        fs >> depths[3];

        if (depths[3] > depths[0])
        {
            increases++;
        }

        depths[0] = depths[1];
        depths[1] = depths[2];
        depths[2] = depths[3];
    }

    fs.close();

    return increases;
}

int main()
{
    auto answer_a = day1a();
    auto answer_b = day1b();

    printf("Day 1\nA: %d\nB: %d\n", answer_a, answer_b);
}

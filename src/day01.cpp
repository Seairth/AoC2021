#include <stdio.h>
#include <fstream>

using namespace std;

#define INPUT_FILENAME "../input/day01.txt"

static int puzzle1()
{
    ifstream fs(INPUT_FILENAME);

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

static int puzzle2()
{
    ifstream fs(INPUT_FILENAME);

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
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 1\nA: %d\nB: %d\n", answer1, answer2);
}

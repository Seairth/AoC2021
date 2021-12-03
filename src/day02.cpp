#include <stdio.h>
#include <fstream>

using namespace std;

#define INPUT_FILENAME "../input/day02.txt"

static int puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    string command = "";
    int distance = 0;

    auto forward_sum = 0;
    auto depth_sum = 0;

    while (fs >> command >> distance)
    {
        if (command == "forward")
        {
            forward_sum += distance;
            continue;
        }
        
        if (command == "down")
        {
            depth_sum += distance;
            continue;
        }

        if (command == "up")
        {
            depth_sum -= distance;
            continue;
        }
    }

    fs.close();

    return forward_sum * depth_sum;
}

static int puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    string command = "";
    int distance = 0;

    auto aim_sum = 0;
    auto forward_sum = 0;
    auto depth_sum = 0;

    while (fs >> command >> distance)
    {
        if (command == "forward")
        {
            forward_sum += distance;
            depth_sum += (aim_sum * distance);
            continue;
        }
        
        if (command == "down")
        {
            aim_sum += distance;
            continue;
        }

        if (command == "up")
        {
            aim_sum -= distance;
            continue;
        }
    }

    fs.close();

    return forward_sum * depth_sum;
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 2\nA: %d\nB: %d\n", answer1, answer2);
}

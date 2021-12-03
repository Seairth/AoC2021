#include <stdio.h>
#include <fstream>

using namespace std;

static int day2a()
{
    ifstream fs("../input/day2.txt");

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

static int day2b()
{
    ifstream fs("../input/day2.txt");

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
    auto answer_a = day2a();
    auto answer_b = day2b();

    printf("Day 2\nA: %d\nB: %d\n", answer_a, answer_b);
}

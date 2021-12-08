#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

#define INPUT_FILENAME "../input/day03.txt"
#define BIT_WIDTH 12

static int puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    int codes = 0;
    int ones[BIT_WIDTH] = {};

    string code;

    while (fs >> code)
    {
        codes++;

        for (auto i = 0; i < BIT_WIDTH; i++)
        {
            if (code[i] == '1')
            {
                ones[i]++;
            }
        }
    }

    fs.close();

    int gamma = 0;
    int epsilon = 0;

    for(auto i = 0; i < BIT_WIDTH; i++)
    {
        gamma <<= 1;
        epsilon <<= 1;

        if (ones[i] > (codes - ones[i]))
        {
            gamma += 1;
        }
        else
        {
            epsilon += 1;
        }
    }

    return gamma * epsilon;
}

static int puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    string code;
    vector<string> codes;

    while (fs >> code) codes.push_back(code);

    fs.close();

    auto oxy(codes);

    for (auto i = 0; i < BIT_WIDTH; i++)
    {
        auto ones = 0;

        for (auto c = oxy.begin(); c != oxy.end(); c++)
        {
            if ((*c)[i] == '1') ones++;
        }

        auto keep = '1';

        if (ones < oxy.size() - ones)
        {
            keep = '0';
        }
        
        auto c = oxy.begin();
        while (c != oxy.end())
        {
            if ((*c)[i] != keep)
            {
                c = oxy.erase(c);
            }
            else
            {
                c++;
            }
        }

        if (oxy.size() == 1) break;
    }

    auto co2(codes);

    for (auto i = 0; i < BIT_WIDTH; i++)
    {
        auto ones = 0;

        for (const auto& c: co2)
        {
            if (c[i] == '1') ones++;
        }

        auto keep = '0';

        if (ones < co2.size() - ones)
        {
            keep = '1';
        }
        
        auto c = co2.begin();
        while (c != co2.end())
        {
            if ((*c)[i] != keep)
            {
                c = co2.erase(c);
            }
            else
            {
                c++;
            }
        }

        if (co2.size() == 1) break;
    }

    auto oxygen_generator_rating = stoi(oxy[0], nullptr, 2);
    auto co2_scrubber_rating = stoi(co2[0], nullptr, 2); 

    return oxygen_generator_rating * co2_scrubber_rating;
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 3\nA: %d\nB: %d\n", answer1, answer2);
}

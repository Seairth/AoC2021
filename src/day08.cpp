#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

#define INPUT_FILENAME "../input/day08.txt"

static uint64_t puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    uint32_t count = 0;
    string value;

    while (! fs.eof())
    {
        fs.ignore(256, '|');
        fs.seekg(1, ios_base::cur);

        for (auto i = 0; i < 4; i++)
        {
            fs >> value;

            auto len = value.length();

            if (len == 2 || len == 3 || len == 4 || len == 7)
            {
                count++;
            }
        }
    }

    fs.close();

    return count;
}

static uint64_t puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    uint32_t count = 0;
    string segments;

    while (!fs.eof())
    {
        map<string, int> digits;
        vector<string> panel;

        for (auto i = 0; i < 10 ; i++)
        {
            fs >> segments;
            sort(segments.begin(), segments.end());
            digits[segments] = -1;
        }

        fs >> segments;  // ignore (pipe)

        for (auto i = 0; i < 4 ; i++)
        {
            fs >> segments;
            sort(segments.begin(), segments.end());
            panel.push_back(segments);
        }

        // 9 = length(6) and contains 4
        // 0 = length(6) and contains 7
        // 3 = length(5) and contains 7
        // 5 = length(5) and contains (4-1)
        // 6 = length(6) and contains (4-1)
        // 2 = last one

        string one;
        string four;
        string seven;

        for (const auto [key, value]: digits)
        {
            if (key.length() == 2)
            {
                one = key;
                digits[one] = 1;
            }
            else if (key.length() == 3)
            {
                seven = key;
                digits[seven] = 7;
            }
            else if (key.length() == 4)
            {
                four = key;
                digits[four] = 4;
            }
            else if (key.length() == 7)
            {
                digits[key] = 8;
            }
        }

        for (const auto [key, value]: digits)
        {
            if (value == -1)
            {
                auto segments_matched = 0;

                for(const auto segment: four)
                {
                    if (key.find(segment) != key.npos)
                    {
                        segments_matched++;
                    }
                }

                if (segments_matched == 4 && key.length() == 6) {
                    digits[key] = 9;
                }
            }
        }

        for (const auto [key, value]: digits)
        {
            if (value == -1)
            {
                auto segments_matched = 0;

                for(const auto segment: seven)
                {
                    if (key.find(segment) != key.npos)
                    {
                        segments_matched++;
                    }
                }

                if (segments_matched == 3) {
                    if (key.length() == 6)
                    {
                        digits[key] = 0;
                    }
                    else if (key.length() == 5)
                    {
                        digits[key] = 3;
                    }
                }
            }
        }


        string four_minus_one;
        const auto begin1 = four_minus_one.begin();

        set_difference(four.begin(), four.end(), one.begin(), one.end(), inserter(four_minus_one, four_minus_one.begin()));

        for (const auto [key, value]: digits)
        {
            if (value == -1)
            {
                auto segments_matched = 0;

                for(const auto segment: four_minus_one)
                {
                    if (key.find(segment) != key.npos)
                    {
                        segments_matched++;
                    }
                }

                if (segments_matched == 2) {
                    digits[key] = key.length(); // 5 or 6
                }
            }
        }

        for (const auto [key, value]: digits)
        {
            if (value == -1)
            {
                digits[key] = 2;
                break;
            }
        }

        uint32_t value = 0;

        for (const auto& digit: panel)
        {
            value = (value * 10) + digits[digit];
        }

        count += value;
    }

    fs.close();

    return count;
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 8\nA: %lu\nB: %lu\n", answer1, answer2);
}

#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

using namespace std;

#define DAY "13"
#define INPUT_FILENAME "../input/day" DAY ".txt"

#define INSTRUCTION_PREFIX "fold"
#define EMPTY_SYMBOL ' '
#define DOT_SYMBOL '#'

static void fold_x(vector<vector<char>>& page, size_t fold_at)
{
    for (auto& row: page)
    {
        for(auto offset = 1; (offset <= fold_at) && ((fold_at + offset) < row.size()); offset++)
        {
            if (row[fold_at - offset] == EMPTY_SYMBOL)
            {
                row[fold_at - offset] = row[fold_at + offset];
            }
        }

        row.resize(fold_at);
    }
}

static void fold_y(vector<vector<char>>& page, size_t fold_at)
{
    for (auto offset = 1; (offset <= fold_at) && ((fold_at + offset) < page.size()); offset++)
    {
        for (auto col = 0; col < page[offset].size(); col++)
        {
            if (page[fold_at - offset][col] == EMPTY_SYMBOL)
            {
                page[fold_at - offset][col] = page[fold_at + offset][col];
            }
        }
    }

    page.resize(fold_at);
}


static uint64_t puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    string input_line;

    auto dots = vector<pair<uint64_t, uint64_t>>{};
    auto instructions = vector<pair<string, uint64_t>>{};
    auto max_x = 0, max_y = 0;

    while (fs >> input_line)
    {
        if (input_line.empty())
            continue;

        if (input_line == INSTRUCTION_PREFIX)
        {
            fs >> input_line >> input_line;
            auto delim = input_line.find('=');

            instructions.push_back({ input_line.substr(0, delim), atoi(input_line.substr(delim + 1).c_str()) });
        }
        else
        {
            auto delim = input_line.find(',');
            auto x = atoi(input_line.substr(0, delim).c_str());
            auto y = atoi(input_line.substr(delim + 1).c_str());
            dots.push_back({ x, y });

            max_x = max(max_x, x);
            max_y = max(max_y, y);
        }
    }

    fs.close();

    // auto page = vector<vector<char>>(max_y + 1, vector(max_x + 1, EMPTY_SYMBOL));
    auto page = vector<vector<char>>{};

    for (auto row = 0; row <= max_y; row++)
    {
        auto _row = vector<char>{};

        for (auto col = 0; col <= max_x; col++)
            _row.push_back(EMPTY_SYMBOL);

        page.push_back(_row);
    }       

    for (const auto& dot: dots)
        page[dot.second][dot.first] = DOT_SYMBOL;

    fold_x(page, instructions[0].second);

    auto dot_count = 0;

    for(const auto& row: page)
        for(const auto col: row)
            dot_count += (col == DOT_SYMBOL ? 1 : 0);

    return dot_count;
}

static uint64_t puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    string input_line;

    auto dots = vector<pair<uint64_t, uint64_t>>{};
    auto instructions = vector<pair<string, uint64_t>>{};
    auto max_x = 0, max_y = 0;

    while (fs >> input_line)
    {
        if (input_line.empty())
            continue;

        if (input_line == INSTRUCTION_PREFIX)
        {
            fs >> input_line >> input_line;
            auto delim = input_line.find('=');

            instructions.push_back({ input_line.substr(0, delim), atoi(input_line.substr(delim + 1).c_str()) });
        }
        else
        {
            auto delim = input_line.find(',');
            auto x = atoi(input_line.substr(0, delim).c_str());
            auto y = atoi(input_line.substr(delim + 1).c_str());
            dots.push_back({ x, y });

            max_x = max(max_x, x);
            max_y = max(max_y, y);
        }
    }

    fs.close();

    auto page = vector<vector<char>>(max_y + 1, vector(max_x + 1, EMPTY_SYMBOL));

    for (const auto& dot: dots)
        page[dot.second][dot.first] = DOT_SYMBOL;

    for (const auto& instruction: instructions)
    {
        if (instruction.first == "x")
            fold_x(page, instruction.second);
        else
            fold_y(page, instruction.second);
    }

    for (const auto& row: page)
    {
        for(auto& col: row)
            printf("%c", col);

        printf("\n");
    }

    return 0;
}

int main()
{
    printf("Day " DAY "\n");
    printf("A: %lu\n", puzzle1());
    printf("B: %lu\n", puzzle2());
}

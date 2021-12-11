#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stack>
#include <list>

using namespace std;

#define INPUT_FILENAME "../input/day11.txt"
#define MAX_ENERGY 9

static uint64_t increment(vector<vector<uint8_t>>& grid, int row, int col)
{
    grid[row][col]++;
    
    uint64_t fired = 0;

    if (grid[row][col] == MAX_ENERGY + 1)
    {
        fired++;

        if (row > 0)
        {
            if (col > 0)
            {
                fired += increment(grid, row-1, col-1);
            }

            fired += increment(grid, row-1, col);

            if (col < grid[row-1].size() - 1)
            {
                fired += increment(grid, row-1, col+1);
            }
        }

        if (col > 0)
        {
            fired += increment(grid, row, col-1);
        }

        if (col < grid[row].size() - 1)
        {
            fired += increment(grid, row, col+1);
        }

        if (row < grid.size() - 1)
        {
            if (col > 0)
            {
                fired += increment(grid, row+1, col-1);
            }

            fired += increment(grid, row+1, col);

            if (col < grid[row+1].size() - 1)
            {
                fired += increment(grid, row+1, col+1);
            }
        }
    }

    return fired;
}

static void reset_flashed(vector<vector<uint8_t>>& grid)
{
    for (auto& r:grid)
        for (auto& c:r)
            if (c > MAX_ENERGY) c = 0;
}

static uint64_t puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    vector<vector<uint8_t>> grid;
    string input_row;

    while(fs >> input_row)
    {
        grid.push_back({});
        
        for (auto c: input_row)
        {
            grid.back().push_back(c - '0');
        }
    }

    fs.close();

    uint64_t flashes = 0;

    for (auto step = 0; step < 100; step++)
    {
        for (auto row = 0; row < grid.size(); row++)
        {
            for (auto col = 0; col < grid[row].size(); col++)
            {
                flashes += increment(grid, row, col);
            }
        }

        reset_flashed(grid);
    }

    return flashes;
}

static uint64_t puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    vector<vector<uint8_t>> grid;
    string input_row;

    while(fs >> input_row)
    {
        grid.push_back({});
        
        for (auto c: input_row)
        {
            grid.back().push_back(c - '0');
        }
    }

    fs.close();

    uint64_t steps = 1;

    for (;; steps++)
    {
        uint64_t flashes = 0;

        for (auto row = 0; row < grid.size(); row++)
        {
            for (auto col = 0; col < grid[row].size(); col++)
            {
                flashes += increment(grid, row, col);
            }
        }

        if (flashes == 100) break;

        reset_flashed(grid);
    }

    return steps;
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 11\nA: %lu\nB: %lu\n", answer1, answer2);
}

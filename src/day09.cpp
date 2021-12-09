#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <list>
#include <numeric>
#include <stack>
#include <vector>

using namespace std;

#define INPUT_FILENAME "../input/day09.txt"
#define MAP_DIM 100

static void init_map(vector<string> &m, istream &f)
{
    string line;
    
    m.push_back(string(MAP_DIM + 2, '9'));

    while(f >> line)
    {
        line.insert(line.begin(), '9');
        line.push_back('9');
        m.push_back(line);
    }

    m.push_back(string(MAP_DIM + 2, '9'));
}

static int32_t flood_basin(vector<string> &m, int32_t row, int32_t col)
{
    stack<pair<int32_t, int32_t>> _stack;
    list<pair<int32_t, int32_t>> visited;

    _stack.push({row, col});

    while (!_stack.empty())
    {
        auto c = _stack.top();
        _stack.pop();

        if (m[c.first][c.second] != '9' && find(visited.begin(), visited.end(), c) == visited.end())
        {
            visited.push_back(c);
            
            _stack.push({c.first + 1, c.second});
            _stack.push({c.first - 1, c.second});
            _stack.push({c.first, c.second + 1});
            _stack.push({c.first, c.second - 1});
        }
    }

    return visited.size();
}

static uint64_t puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    vector<string> heightmap;

    init_map(heightmap, fs);

    fs.close();

    list<int32_t> low_points;

    for (auto row = 1; row < heightmap.size() - 1; row++)
    {
        for (auto col = 1; col < heightmap[row].size() - 1; col++)
        {
            const auto value = heightmap[row][col];
            if (value >= heightmap[row-1][col]) continue;
            if (value >= heightmap[row+1][col]) continue;
            if (value >= heightmap[row][col-1]) continue;
            if (value >= heightmap[row][col+1]) continue;
            
            low_points.push_back(value - '0');
        }
    }

    return accumulate(low_points.begin(), low_points.end(), 0) + low_points.size();
}

static uint64_t puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    vector<string> heightmap;

    init_map(heightmap, fs);

    fs.close();

    list<int32_t> basins;

    for (auto row = 1; row < heightmap.size() - 1; row++)
    {
        for (auto col = 1; col < heightmap[row].size() - 1; col++)
        {
            const auto value = heightmap[row][col];
            if (value >= heightmap[row-1][col]) continue;
            if (value >= heightmap[row+1][col]) continue;
            if (value >= heightmap[row][col-1]) continue;
            if (value >= heightmap[row][col+1]) continue;
            
            basins.push_back(flood_basin(heightmap, row, col));
        }
    }

    basins.sort();

    auto answer = 1;

    answer *= basins.back(); basins.pop_back();
    answer *= basins.back(); basins.pop_back();
    answer *= basins.back();

    return answer;
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 9\nA: %lu\nB: %lu\n", answer1, answer2);
}

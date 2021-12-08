#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

#define INPUT_FILENAME "../input/day05.txt"


static int solve(bool diagonal)
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    map<int, map<int, int>> grid;

    while (! fs.eof())
    {
        string p1, p2, _;

        fs >> p1 >> _ >> p2;

        replace(p1.begin(), p1.end(), ',', ' ');
        replace(p2.begin(), p2.end(), ',', ' ');

        istringstream point1(p1);
        istringstream point2(p2);

        int x1, y1, x2, y2;
        point1 >> x1 >> y1;
        point2 >> x2 >> y2;

        auto x_dir = x1 < x2 ? 1 : -1;
        auto y_dir = y1 < y2 ? 1 : -1;

        if (x1 == x2)
        {
            if (grid.find(x1) == grid.end()) grid[x1] = {};
            
            for (auto i = y1; (y_dir == 1 && i <= y2) || (y_dir == -1 && i >= y2); i+=y_dir)
            {
                if (grid[x1].find(i) == grid[x1].end()) grid[x1][i] = 0;
                
                grid[x1][i]++;
            }
        }
        else if (y1 == y2)
        {
            for (auto i = x1; (x_dir == 1 && i <= x2) || (x_dir == -1 && i >= x2); i+=x_dir)
            {
                if (grid.find(i) == grid.end()) grid[i] = {};
                if (grid[i].find(y1) == grid[i].end()) grid[i][y1] = 0;
                
                grid[i][y1]++;
            }
        }
        else if (diagonal == true)
        {
            for (auto i = x1, j = y1; ((x_dir == 1 && i <= x2) || (x_dir == -1 && i >= x2)) && ((y_dir == 1 && j <= y2) || (y_dir == -1 && j >= y2)); i+=x_dir, j+=y_dir)
            {
                if (grid.find(i) == grid.end()) grid[i] = {};
                if (grid[i].find(j) == grid[i].end()) grid[i][j] = 0;
                
                grid[i][j]++;
            }
        }
    }

    fs.close();

    int answer = 0;

    for (const auto& x: grid)
    {
        auto subgrid = x.second;

        for (const auto& y: subgrid)
        {
            if (y.second > 1)
            {
                answer++;
            }
        }
    }

    return answer;

}


static int puzzle1()
{
    return solve(false);
}

static int puzzle2()
{
    return solve(true);
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 5\nA: %d\nB: %d\n", answer1, answer2);
}

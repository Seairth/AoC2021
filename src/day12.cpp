#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

using namespace std;

#define DAY "12"
#define INPUT_FILENAME "../input/day" DAY ".txt"

#define START "start"
#define END   "end"

template<class Iter>
struct iter_pair_range : std::pair<Iter,Iter> {
    iter_pair_range(std::pair<Iter,Iter> const& x)
    : std::pair<Iter,Iter>(x)
    {}
    Iter begin() const {return this->first;}
    Iter end()   const {return this->second;}
};

template<class Iter>
inline iter_pair_range<Iter> as_range(std::pair<Iter,Iter> const& x)
{ return iter_pair_range<Iter>(x); }

static vector<list<string>> traverse(list<string>& root, multimap<string, string>& paths, bool extra_paths)
{
    vector<list<string>> solutions = {};

    for (auto& path: as_range(paths.equal_range(root.back())))
    {
        if (path.second == START) continue;

        if (path.second[0] >= 'a' && path.second[0] <= 'z' && path.second != END)
        {
            if (find(root.begin(), root.end(), path.second) != root.end())
            {
                if (extra_paths)
                {
                    auto begin = root.begin();
                    auto end = root.end();

                    while (begin != end)
                    {
                        if ((*begin)[0] >= 'a' && (*begin)[0] <= 'z') {
                            auto compare = begin;
                            compare++;

                            while (compare != end)
                            {
                                if (*begin == *compare) break;
                                compare++;
                            }

                            if (compare != end) break;
                        }

                        begin++;
                    }

                    if (begin != end) continue;
                }
                else
                {
                    continue;
                }
            }
        }

        auto new_root = root;
        new_root.push_back(path.second);

        if (path.second == END)
        {
            solutions.push_back(new_root);
        }
        else
        {
            auto child_solutions = traverse(new_root, paths, extra_paths);

            solutions.insert(solutions.end(), make_move_iterator(child_solutions.begin()), make_move_iterator(child_solutions.end()));
        }
    }

    return solutions;
}

static uint64_t puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    auto paths = multimap<string, string>{};
    auto input_line = string{};

    while (fs >> input_line)
    {
        auto index = input_line.find('-');
        paths.insert({ input_line.substr(0, index),  input_line.substr(index + 1) });
        paths.insert({ input_line.substr(index + 1),  input_line.substr(0, index) });
    }

    fs.close();

    auto start = list<string>{ START };

    vector<list<string>> solutions = traverse(start, paths, false);

    return solutions.size();
}

static uint64_t puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    auto paths = multimap<string, string>{};
    auto input_line = string{};

    while (fs >> input_line)
    {
        auto index = input_line.find('-');
        paths.insert({ input_line.substr(0, index),  input_line.substr(index + 1) });
        paths.insert({ input_line.substr(index + 1),  input_line.substr(0, index) });
    }

    fs.close();

    auto start = list<string>{ START };

    vector<list<string>> solutions = traverse(start, paths, true);

    return solutions.size();
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day " DAY "\nA: %lu\nB: %lu\n", answer1, answer2);
}

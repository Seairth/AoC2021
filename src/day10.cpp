#include <stdio.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <stack>
#include <list>

using namespace std;

#define INPUT_FILENAME "../input/day10.txt"

static pair<bool, string> find_chars(string& input)
{
    stack<char> _stack = {};

    for (auto c: input)
    {
        switch (c)
        {
        case '(':
        case '{':
        case '[':
        case '<':
            _stack.push(c);
            continue;
        
        case ')':
            if (_stack.top() == '(')
            {
                _stack.pop();
                continue;
            }
            break;
        
        case '}':
            if (_stack.top() == '{')
            {
                _stack.pop();
                continue;
            }
            break;
        
        case ']':
            if (_stack.top() == '[')
            {
                _stack.pop();
                continue;
            }
            break;
        
        case '>':
            if (_stack.top() == '<')
            {
                _stack.pop();
                continue;
            }
            break;
        }
        
        return { false, string(1, c) };
    }

    string closing;

    while (!_stack.empty())
    {
        switch (_stack.top())
        {
        case '(':
            closing.push_back(')');
            break;
        
        case '{':
            closing.push_back('}');
            break;

        case '[':
            closing.push_back(']');
            break;

        case '<':
            closing.push_back('>');
            break;
        }

        _stack.pop();
    }

    return { true, closing };
}

static uint64_t puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    uint64_t score = 0;

    map<char, uint64_t> values = {
        { ')', 3 },
        { ']', 57 },
        { '}', 1197 },
        { '>', 25137 }
    };

    string line;

    while (fs >> line)
    {
        auto [found, value] = find_chars(line);

        if (!found)
        {
            score += values[value[0]];
        }
    }

    fs.close();

    return score;
}

static uint64_t puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    auto scores = list<uint64_t>{};
    
    map<char, uint64_t> values = {
        { ')', 1 },
        { ']', 2 },
        { '}', 3 },
        { '>', 4 }
    };

    string line;

    while (fs >> line)
    {
        auto [found, value] = find_chars(line);

        if (found)
        {
            uint64_t score = 0;

            for (auto c: value)
            {
                score = (score * 5) + values[c];
            }

            scores.push_back(score);
        }
    }

    fs.close();

    scores.sort();

    auto middle = (scores.size() - 1)/2;
    auto iter = scores.begin();

    advance(iter, middle);

    return *iter;
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 10\nA: %lu\nB: %lu\n", answer1, answer2);
}

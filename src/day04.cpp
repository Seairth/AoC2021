#include <stdio.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#define INPUT_FILENAME "../input/day04.txt"
#define CARD_SIZE 5

static bool is_winning_card(int* card)
{
    for(auto row = 0; row < CARD_SIZE; row++)
    {
        auto sum = 0;

        for (auto col = 0; col < CARD_SIZE; col++) sum += card[row*CARD_SIZE + col];

        if (sum == 0) return true;
    }

    for(auto col = 0; col < CARD_SIZE; col++)
    {
        auto sum = 0;

        for (auto row = 0; row < CARD_SIZE; row++) sum += card[row*CARD_SIZE + col];

        if (sum == 0) return true;
    }

    return false;
}

static int puzzle1()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    vector<int> numbers;
    vector<int*> cards;

    string input;
    int value = 0;
    int temp_card[CARD_SIZE * CARD_SIZE] = {};

    fs >> input;

    replace(input.begin(), input.end(), ',', ' ');

    istringstream random_numbers(input);

    while (random_numbers >> value) numbers.push_back(value);

    while(! fs.eof())
    {
        for(auto i = 0; i < CARD_SIZE * CARD_SIZE; i++) fs >> temp_card[i];
        
        auto card = new int[CARD_SIZE * CARD_SIZE];
        auto p_c = card;
        auto p_tc = temp_card;

        for(auto i = 0; i < CARD_SIZE*CARD_SIZE; i++) *(p_c++) = *(p_tc++);
        
        cards.push_back(card);
    }

    fs.close();

    auto answer = 0;

    for (const auto number: numbers)
    {
        for (const auto& card: cards)
        {
            for (auto i = 0; i < CARD_SIZE * CARD_SIZE; i++)
            {
                if (card[i] == number)
                {
                    card[i] = 0;

                    if (is_winning_card(card))
                    {
                        for (auto i2 = 0; i2 < CARD_SIZE * CARD_SIZE; i2++) answer += card[i2];
                        answer *= number;
                        break;
                    }
                }
            }

            if (answer > 0) break;
        }

        if (answer > 0) break;
    }

    for (auto card: cards) delete[] card;

    return answer;
}

static int puzzle2()
{
    ifstream fs(INPUT_FILENAME);

    if (fs.fail())
    {
        printf("failed to open input file.");
        return -1;
    }

    vector<int> numbers;
    vector<int*> cards;

    string input;
    int value = 0;
    int temp_card[CARD_SIZE * CARD_SIZE] = {};

    fs >> input;

    replace(input.begin(), input.end(), ',', ' ');

    istringstream random_numbers(input);

    while (random_numbers >> value) numbers.push_back(value);

    while(! fs.eof())
    {
        for(auto i = 0; i < CARD_SIZE * CARD_SIZE; i++) fs >> temp_card[i];
        
        auto card = new int[CARD_SIZE * CARD_SIZE];
        auto p_c = card;
        auto p_tc = temp_card;

        for(auto i = 0; i < CARD_SIZE*CARD_SIZE; i++) *(p_c++) = *(p_tc++);
        
        cards.push_back(card);
    }

    fs.close();

    auto answer = 0;

    for (const auto number: numbers)
    {
        auto c = cards.begin();

        while(c != cards.end())
        {
            auto deleted = false;
            auto card = *c;

            for (auto i = 0; i < CARD_SIZE * CARD_SIZE; i++)
            {
                if (card[i] == number)
                {
                    card[i] = 0;

                    if (is_winning_card(card))
                    {
                        if (cards.size() > 1)
                        {
                            delete[] card;
                            c = cards.erase(c);
                            deleted = true;
                        }
                        else
                        {
                            for (auto i2 = 0; i2 < CARD_SIZE * CARD_SIZE; i2++) answer += card[i2];
                            answer *= number;
                            break;
                        }
                    }
                }
            }

            if (answer > 0) break;

            if (deleted)
            {
                deleted = false;
            }
            else
            {
                c++;
            }
        }

        if (answer > 0) break;
    }

    for (auto card: cards) delete[] card;

    return answer;
}

int main()
{
    auto answer1 = puzzle1();
    auto answer2 = puzzle2();

    printf("Day 4\nA: %d\nB: %d\n", answer1, answer2);
}

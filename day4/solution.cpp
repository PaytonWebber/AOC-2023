#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

class Card
{
public:
    vector<int> winning_numbers;
    vector<int> my_numbers;
    int matches = 0;
};

int get_card_points(string line)
{
    Card card;

    bool winner_side = true;
    stringstream ss(line);
    string token;
    while (ss >> token)
    {
        bool is_number = true;
        if (token == "|")
        {
            winner_side = false;
            continue;
        }

        for (int i = 0; i < token.length(); i++)
        {
            if (!isdigit(token[i]))
            {
                is_number = false;
                break;
            }
        }
        if (!is_number) { continue; }

        if (winner_side)
        {
            card.winning_numbers.push_back(stoi(token));
        }
        else
        {
            card.my_numbers.push_back(stoi(token));
        }
    }

    for (int i = 0; i < card.my_numbers.size(); i++)
    {
        for (int j = 0; j < card.winning_numbers.size(); j++)
        {
            if (card.my_numbers[i] == card.winning_numbers[j])
            {
                card.matches++;
            }
        }
    }
    if (card.matches == 0) { return 0; };

    return pow(2, card.matches - 1);
}

void parse_input()
{
    int total = 0;
    int count = 1;
    string line;
    while (getline(cin, line))
    {
        int temp = get_card_points(line);
        cout << "Card " << count << " has " << temp << " points." << endl; 
        total += temp;
        count++;
    }
    cout << total << endl;
}

int main()
{
    parse_input();
    return 0;
}

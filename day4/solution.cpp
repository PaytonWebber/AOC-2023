#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <math.h>

using namespace std;

class Card
{
    public:
    vector<int> winning_numbers;
    vector<int> my_numbers;
    int matches = 0;
};

void determine_card_matches(Card& card)
{
    for (size_t i = 0; i < card.my_numbers.size(); i++)
    {
        for (size_t j = 0; j < card.winning_numbers.size(); j++)
        {
            if (card.my_numbers[i] == card.winning_numbers[j])
            {
                card.matches++;
            }
        }
    }
    return;
}

Card create_card(string line)
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

        for (unsigned long i = 0; i < token.length(); i++)
        {
            if (!isdigit(token[i]))
            {
                is_number = false;
                break;
            }
        }
        if (!is_number) { continue; }

        if (winner_side) { card.winning_numbers.push_back(stoi(token)); }
        else { card.my_numbers.push_back(stoi(token)); }
    }

    determine_card_matches(card);
    return card;
}

int get_card_points(Card card) { return pow(2, card.matches - 1); }

int get_card_copies(const int main_card, const vector<Card>& cards)
{
    clog << "\rMain card: " << main_card << " " << flush;

    int copies = 1;
    for (size_t i = 1; i <= (unsigned long)cards[main_card].matches && (main_card + i) < cards.size(); i++)
    {
        copies += get_card_copies(main_card + i, cards);
    }

    return copies;
}

void parse_input()
{
    int output = 0;
    int count = 0;
    Card card;

    #ifdef PART2
    vector<Card> cards;
    #endif

    string line;
    while (getline(cin, line))
    {
        count++;
        card = create_card(line);

        #ifdef PART2
        cards.push_back(card);
        #endif

        #ifdef PART1
        output += get_card_points(card);
        #endif
    }

    #ifdef PART2
    for (size_t i = 0; i < cards.size(); i++)
    {
        output += get_card_copies(i, cards);
    }
    #endif

    cout << endl;
    cout << output << endl;
}

int main()
{
    auto start = chrono::steady_clock::now();

    parse_input();

    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    clog << "Time: " << duration << " ms" << endl;

    return 0;
}

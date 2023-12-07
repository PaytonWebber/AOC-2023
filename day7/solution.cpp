#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <map>

using namespace std;

class hand
{
    public:
    string cards;
    int bid;
    int strength;
};

bool operator>(const hand &h1, const hand& h2)
{
    map<char, int> card_strength;
    card_strength['A'] = 14;
    card_strength['K'] = 13;
    card_strength['Q'] = 12;
    #ifdef PART1
    card_strength['J'] = 11;
    #else
    card_strength['J'] = 1;
    #endif
    card_strength['T'] = 10;
    card_strength['9'] = 9;
    card_strength['8'] = 8;
    card_strength['7'] = 7;
    card_strength['6'] = 6;
    card_strength['5'] = 5;
    card_strength['4'] = 4;
    card_strength['3'] = 3;
    card_strength['2'] = 2;

    for (int i = 0; i < 5; i++)
    {
        if (card_strength[h1.cards[i]] > card_strength[h2.cards[i]])
        {
            return true;
        }
        else if (card_strength[h1.cards[i]] < card_strength[h2.cards[i]])
        {
            return false;
        }
    }
    return false;
}

vector<hand> get_ordered_hands(vector<hand> &hands)
{
    vector<hand> ordered_hands;
    ordered_hands.reserve(hands.size());
    for (const auto& h : hands)
    {
        if (ordered_hands.size() == 0) { ordered_hands.push_back(h); }
        else
        {
            bool insert = false;
            for (size_t i = ordered_hands.size() - 1; i >= 0; i--)
            {
                if (h.strength >= ordered_hands[i].strength)
                {
                    if (h.strength == ordered_hands[i].strength)
                    {
                        if (h > ordered_hands[i]) { insert = true; }
                    }
                    else { insert = true; }
                }
                if (insert)
                {
                    ordered_hands.insert(ordered_hands.begin() + i + 1, h);
                    break;
                }
            }
            if (!insert) { ordered_hands.insert(ordered_hands.begin(), h); }
        }
    }
    return ordered_hands;
}

void get_strength(vector<hand> &hands)
{
    map<char, int> card_count;
    for (auto& h : hands)
    {
        #ifdef PART2
        int num_jokers = 0;
        #endif
        for (int i = 0; i < 5; i++)
        {
            #ifdef PART2
            if (h.cards[i] == 'J') { num_jokers++; }

            else if (card_count.find(h.cards[i]) == card_count.end())
            {
                card_count[h.cards[i]] = 1;
            }
            #else
            if (card_count.find(h.cards[i]) == card_count.end())
            {
                card_count[h.cards[i]] = 1;
            }
            #endif
            else { card_count[h.cards[i]]++; }
        }

        #ifdef PART2
        for (int i = 0; i < num_jokers; i++)
        {
            int max_count = 0;
            char max_card;
            for (const auto& c : card_count)
            {
                if (c.second > max_count)
                {
                    max_count = c.second;
                    max_card = c.first;
                }
            }
            card_count[max_card]++;
        }
        #endif

        if (card_count.size() == 1) { h.strength = 7; }
        else if (card_count.size() == 2)
        {
            for (int i = 0; i < 5; i++)
            {
                if (card_count[h.cards[i]] == 4)
                {
                    h.strength = 6;
                    break;
                }
                else if (card_count[h.cards[i]] == 3)
                {
                    h.strength = 5;
                    break;
                }
            }
        }
        else if (card_count.size() == 3)
        {
            for (int i = 0; i < 5; i++)
            {
                if (card_count[h.cards[i]] == 3)
                {
                    h.strength = 4;
                    break;
                }
                else if (card_count[h.cards[i]] == 2)
                {
                    h.strength = 3;
                    break;
                }
            }
        }
        else if (card_count.size() == 4) { h.strength = 2; }
        else { h.strength = 1; }

        card_count.clear();
    }
    return;
}

void parse_input()
{
    vector<hand> hands;
    string line;
    while (getline(cin, line))
    {
        stringstream ss(line);
        string card;
        hand h;
        ss >> card;
        h.cards = card;
        ss >> card;
        h.bid = stoi(card);
        hands.push_back(h);
    }
    get_strength(hands);

    vector<hand> ordered_hands = get_ordered_hands(hands);

    int output = 0;
    for (size_t i = 0; i < ordered_hands.size(); i++)
    {
        output += ordered_hands[i].bid * (i + 1);
    }
    cout << output << endl;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    parse_input();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << duration.count() << "ms" << endl;

    return 0;
}

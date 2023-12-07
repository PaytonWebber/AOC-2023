#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class hand
{
    public:
    string cards;
    unsigned long bid;
    string strength;
};

vector<hand> get_ordered_hands(vector<hand> &hands)
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

    vector<hand> ordered_hands;
    for (auto h : hands)
    {
        if (ordered_hands.size() == 0)
        {
            ordered_hands.push_back(h);
        }
        else
        {
            bool inserted = false;
            for (size_t i = 0; i < ordered_hands.size(); i++)
            {
                if (inserted)
                {
                    break;
                }
                if (h.strength == "Five of a Kind")
                {
                   if (ordered_hands[i].strength == "Five of a Kind")
                   {
                       for (int j = 0; j < 5; j++)
                       {
                           if (card_strength[h.cards[j]] > card_strength[ordered_hands[i].cards[j]])
                           {
                               ordered_hands.insert(ordered_hands.begin() + i, h);
                               inserted = true;

                               break;
                           }
                           else if (card_strength[h.cards[j]] < card_strength[ordered_hands[i].cards[j]])
                           {
                               break;
                           }
                       }
                   }
                   else
                   {
                       ordered_hands.insert(ordered_hands.begin() + i, h);
                       inserted = true;
                       break;
                   } 
                }
                else if (h.strength == "Four of a Kind")
                {
                    if (ordered_hands[i].strength == "Five of a Kind")
                    {
                        continue;
                    }
                    else if (ordered_hands[i].strength == "Four of a Kind")
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (card_strength[h.cards[j]] > card_strength[ordered_hands[i].cards[j]])
                            {
                                ordered_hands.insert(ordered_hands.begin() + i, h);
                                inserted = true;
                                break;
                            }
                            else if (card_strength[h.cards[j]] < card_strength[ordered_hands[i].cards[j]])
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        ordered_hands.insert(ordered_hands.begin() + i, h);
                        inserted = true;
                        break;
                    }
                }
                else if (h.strength == "Full House")
                {
                    if (ordered_hands[i].strength == "Five of a Kind" || ordered_hands[i].strength == "Four of a Kind")
                    {
                        continue;
                    }
                    else if (ordered_hands[i].strength == "Full House")
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (card_strength[h.cards[j]] > card_strength[ordered_hands[i].cards[j]])
                            {
                                ordered_hands.insert(ordered_hands.begin() + i, h);
                                inserted = true;
                                break;
                            }
                            else if (card_strength[h.cards[j]] < card_strength[ordered_hands[i].cards[j]])
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        ordered_hands.insert(ordered_hands.begin() + i, h);
                        inserted = true;
                        break;
                    }
                }
                else if (h.strength == "Three of a Kind")
                {
                    if (ordered_hands[i].strength == "Five of a Kind" || ordered_hands[i].strength == "Four of a Kind" || ordered_hands[i].strength == "Full House")
                    {
                        continue;
                    }
                    else if (ordered_hands[i].strength == "Three of a Kind")
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (card_strength[h.cards[j]] > card_strength[ordered_hands[i].cards[j]])
                            {
                                ordered_hands.insert(ordered_hands.begin() + i, h);
                                inserted = true;
                                break;
                            }
                            else if (card_strength[h.cards[j]] < card_strength[ordered_hands[i].cards[j]])
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        ordered_hands.insert(ordered_hands.begin() + i, h);
                        inserted = true;
                        break;
                    }
                }
                else if (h.strength == "Two Pair")
                {

                    if (ordered_hands[i].strength == "Five of a Kind" || ordered_hands[i].strength == "Four of a Kind" || ordered_hands[i].strength == "Full House" || ordered_hands[i].strength == "Three of a Kind")
                    {
                        continue;
                    }
                    else if (ordered_hands[i].strength == "Two Pair")
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (card_strength[h.cards[j]] > card_strength[ordered_hands[i].cards[j]])
                            {
                                ordered_hands.insert(ordered_hands.begin() + i, h);
                                inserted = true;
                                break;
                            }
                            else if (card_strength[h.cards[j]] < card_strength[ordered_hands[i].cards[j]])
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        ordered_hands.insert(ordered_hands.begin() + i, h);
                        inserted = true;
                        break;
                    }
                }
                else if (h.strength == "One Pair")
                {
                    if (ordered_hands[i].strength == "Five of a Kind" || ordered_hands[i].strength == "Four of a Kind" || ordered_hands[i].strength == "Full House" || ordered_hands[i].strength == "Three of a Kind" || ordered_hands[i].strength == "Two Pair")
                    {
                        continue;
                    }
                    else if (ordered_hands[i].strength == "One Pair")
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (card_strength[h.cards[j]] > card_strength[ordered_hands[i].cards[j]])
                            {
                                ordered_hands.insert(ordered_hands.begin() + i, h);
                                inserted = true;
                                break;
                            }
                            else if (card_strength[h.cards[j]] < card_strength[ordered_hands[i].cards[j]])
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        ordered_hands.insert(ordered_hands.begin() + i, h);
                        inserted = true;
                        break;
                    }
                }
                else if (h.strength == "High Card")
                {
                    if (ordered_hands[i].strength == "Five of a Kind" || ordered_hands[i].strength == "Four of a Kind" || ordered_hands[i].strength == "Full House" || ordered_hands[i].strength == "Three of a Kind" || ordered_hands[i].strength == "Two Pair" || ordered_hands[i].strength == "One Pair")
                    {
                        continue;
                    }
                    else if (ordered_hands[i].strength == "High Card")
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            if (card_strength[h.cards[j]] > card_strength[ordered_hands[i].cards[j]])
                            {
                                ordered_hands.insert(ordered_hands.begin() + i, h);
                                inserted = true;
                                break;
                            }
                            else if (card_strength[h.cards[j]] < card_strength[ordered_hands[i].cards[j]])
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        ordered_hands.insert(ordered_hands.begin() + i, h);
                        inserted = true;
                        break;
                    }
                }
            }
            if (!inserted)
            {
                ordered_hands.push_back(h);
            }
        }
    }

    // I did it the wrong way and relized too late...
    reverse(ordered_hands.begin(), ordered_hands.end());
    return ordered_hands;
}

vector<hand> get_strength(vector<hand> &hands)
{
    vector<hand> hands_with_strength;
    map<char, int> card_count;
    for (auto h : hands)
    {
        #ifdef PART2
        int num_jokers = 0;
        #endif
        for (unsigned long i = 0; i < 5; i++)
        {
            #ifdef PART2
            if (h.cards[i] == 'J')
            {
                num_jokers++;
            }

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
            else
            {
                card_count[h.cards[i]]++;
            }
        }

        #ifdef PART2
        for (int i = 0; i < num_jokers; i++)
        {
            int max_count = 0;
            char max_card;
            for (auto c : card_count)
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

        if (card_count.size() == 1)
        {
            h.strength = "Five of a Kind";
        }
        else if (card_count.size() == 2)
        {
            for (int i = 0; i < 5; i++)
            {
                if (card_count[h.cards[i]] == 4)
                {
                    h.strength = "Four of a Kind";
                    break;
                }
                else if (card_count[h.cards[i]] == 3)
                {
                    h.strength = "Full House";
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
                    h.strength = "Three of a Kind";
                    break;
                }
                else if (card_count[h.cards[i]] == 2)
                {
                    h.strength = "Two Pair";
                    break;
                }
            }
        }
        else if (card_count.size() == 4)
        {
            h.strength = "One Pair";
        }
        else
        {
            h.strength = "High Card";
        }
        card_count.clear();
        hands_with_strength.push_back(h);
    }

    return hands_with_strength;
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
        h.bid = stol(card);
        hands.push_back(h);
    }
    vector<hand> strength_hands = get_strength(hands);

    vector<hand> ordered_hands = get_ordered_hands(strength_hands);

    unsigned long output = 0;
    for (size_t i = 0; i < ordered_hands.size(); i++)
    {
        output += ordered_hands[i].bid * (i + 1);
    }
    cout << output << endl;
}

int main()
{
    parse_input();
    return 0;
}

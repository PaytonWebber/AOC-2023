#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <map>

using namespace std;

const bool is_game_valid(istream &game)
{
    int val;
    string word;
    while (game >> val >> word)
    {
        if (word == "red," || word == "red;" || word == "red")
        {
            if (val > 12) { return false; }
        }
        else if (word == "green," || word == "green;" || word == "green")
        {
            if (val > 13) { return false; }
        }
        else if (word == "blue," || word == "blue;" || word == "blue")
        {
            if (val > 14) { return false; }
        }
    }
    return true;
}

const int get_powerset(istream &game)
{
    map<string, int> mp;

    int val;
    string word;
    while (game >> val >> word)
    {
        if (word == "red," || word == "red;" || word == "red")
        {
            if (val > mp["red"]) { mp["red"] = val; }
        }
        else if (word == "green," || word == "green;" || word == "green")
        {
            if (val > mp["green"]) { mp["green"] = val; }
        }
        else if (word == "blue," || word == "blue;" || word == "blue")
        {
            if (val > mp["blue"]) { mp["blue"] = val; }
        }
    }
    return mp["blue"] * mp["red"] * mp["green"];
}

void parse_input()
{
    int output = 0;

    #ifdef PART1
    int game_id = 1;
    #endif

    string line;
    string temp;
    while (getline(cin, line))
    {
        // get rid of "Game" at the start of each line
        line = line.substr(5, line.length() - 5);

        istringstream iss(line);

        // get rid of the game id
        iss >> temp;
        line = line.substr(temp.length() + 1, line.length() - temp.length() - 1);
        iss = istringstream(line);

        #ifdef PART1
        if (is_game_valid(iss)) { output += game_id; }
        game_id++;
        #endif

        #ifdef PART2
        output += get_powerset(iss);
        #endif
    }
    cout << output << endl;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    parse_input();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    clog << "Time: " << duration.count() << " ms" << endl;

    return 0;
}

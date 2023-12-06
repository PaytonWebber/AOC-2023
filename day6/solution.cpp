#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;

class races
{
    public:
    vector<unsigned long long> times;
    vector<unsigned long long> distances;
};

unsigned long long get_size_of_win_conditions(unsigned long long time, unsigned long long threshold)
{
    vector<unsigned long long> win_conditions;
    for (unsigned long long i = 1; i < time; i++)
    {
        unsigned long long distance = i * (time - i);
        if (distance > threshold) { win_conditions.push_back(distance); }
    }
    return win_conditions.size();
}

void parse_input()
{
    string line;
    races r;
    bool is_time = true;

    #ifdef PART2
    while (getline(cin, line))
    {
        stringstream ss(line);
        string token;
        ss >> token;
        if (token == "Distance:") { is_time = false; }

        string cat_token = "";
        while (ss >> token) { cat_token += token; }

        if (is_time) { r.times.push_back(stoll(cat_token)); }
        else { r.distances.push_back(stoll(cat_token)); }
    }
    #endif

    #ifdef PART1
    while (getline(cin, line))
    {
        stringstream ss(line);
        string token;
        ss >> token;
        if (token == "Distance:") { is_time = false; }

        while (ss >> token)
        {
            if (is_time) { r.times.push_back(stoi(token)); }
            else { r.distances.push_back(stoi(token)); }
        }
    }
    #endif

    unsigned long long output = 1;
    #ifdef PART1
    for (size_t i = 0; i < r.times.size(); i++)
    {
        output *= get_size_of_win_conditions(r.times[i], r.distances[i]);
    }
    #endif

    #ifdef PART2
    output = get_size_of_win_conditions(r.times[0], r.distances[0]);
    #endif

    cout << output << endl;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    parse_input();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time: " << duration.count() << "ms" << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <chrono>

using namespace std;

class node
{
    public:
        string name;
        vector<string> children;
};

unsigned long part2(const string& movements, map<string, node>& nodes, const string& start_node)
{
    unsigned long count = 0;
    unsigned long cur_step = 0;
    string cur_node = start_node;
    while (cur_node[2] != 'Z')
    {
        if (movements[cur_step] == 'L')
        {
            cur_node = nodes[cur_node].children[0];
        }
        else { cur_node = nodes[cur_node].children[1]; }

        cur_step++;
        if (cur_step == movements.length()) { cur_step = 0; }
        count++;
    }
    return count;
}

unsigned long part1(const string& movements, map<string, node>& nodes)
{
    unsigned long count = 0;
    unsigned long cur_step = 0;
    string cur_node = nodes.begin()->first;
    while (cur_node != "ZZZ")
    {
        if (movements[cur_step] == 'L')
        {
            cur_node = nodes[cur_node].children[0];
        }
        else { cur_node = nodes[cur_node].children[1]; }

        cur_step++;
        if (cur_step == movements.length()) { cur_step = 0; }
        count++;
    }
    return count;
}

void parse_input()
{
    unsigned long output = 0;
    map<string, node> nodes;
    string line;

    string movements;
    getline(cin, line);
    while (line != "")
    {
        movements += line;
        getline(cin, line);
    }

    string token;
    while (getline(cin, line))
    {
        node n;
        stringstream ss(line);
        ss >> n.name;
        ss >> token; // Ignore equal sign

        ss >> token;
        n.children.push_back(token.substr(1, token.length() - 2)); 

        ss >> token;
        n.children.push_back(token.substr(0, token.length() - 1));

        nodes[n.name] = n;
    }

    #ifdef PART2
    vector<int> outputs;
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if (it->first[2] == 'A')
        {
            outputs.push_back(part2(movements, nodes, it->first));
        }
    }
    unsigned long lcm = outputs[0];
    for (size_t i = 1; i < outputs.size(); i++)
    {
        unsigned long a = lcm;
        unsigned long b = outputs[i];
        while (a != b)
        {
            if (a < b) { a += lcm; }
            else { b += outputs[i]; }
        }
        lcm = a;
    }
    output = lcm;
    #else
    output = part1(movements, nodes);
    #endif

    cout << output << endl;
    return;
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

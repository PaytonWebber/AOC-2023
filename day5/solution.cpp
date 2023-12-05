#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class range
{
    public:
    unsigned long long dest;
    unsigned long long source;
    unsigned long long length;
};

class map
{
    public:
    string name;
    vector<range> mapping;
};

class seed
{
    public:
    vector<int> dest_values; 
};

unsigned long long dest_value(const unsigned long long& source, const range& r)
{
    unsigned long long offset = source - r.source;
    if(offset < 0) { cout << "ERROR: offset is negative" << endl; }
    return r.dest + offset;
}

bool falls_in_range(unsigned long long value, range r)
{
    if(value >= r.source && value <= r.source + r.length)
    {
        return true;
    }
    return false;
}

unsigned long long get_lowest_location(const vector<map>& maps, vector<seed>& seeds)
{
    for(int i = 0; i < seeds.size(); i++)
    {
        for(int j = 0; j < maps.size(); j++)
        {
            for(int k = 0; k < maps[j].mapping.size(); k++)
            {
                if(falls_in_range(seeds[i].dest_values[j], maps[j].mapping[k]))
                {
                    seeds[i].dest_values.push_back(dest_value(seeds[i].dest_values[j], maps[j].mapping[k]));
                    break;
                } 
                else if (k == maps[j].mapping.size() - 1)
                {
                    seeds[i].dest_values.push_back(seeds[i].dest_values[j]);
                    break;
                }
            }
        }
    }

    unsigned long long lowest_location = seeds[0].dest_values[seeds[0].dest_values.size()-1];
    for(int i = 1; i < seeds.size(); i++)
    {
        if(seeds[i].dest_values[seeds[i].dest_values.size()-1] < lowest_location)
        {
            lowest_location = seeds[i].dest_values[seeds[i].dest_values.size()-1];
        }
    }
    return lowest_location;
}

void parse_input()
{
    vector<map> maps; 
    for(int i = 0; i < 7; i++)
    {
        map m;
        maps.push_back(m);
    }
    
    string line;
    getline(cin, line);
    line = line.substr(7, line.length()-7);
    stringstream ss(line);

    vector<seed> seeds;
    string token;
    while (ss >> token)
    {
        seed s;
        s.dest_values.push_back(stoll(token));
        seeds.push_back(s);
    }

    int map_index = -1;
    while (getline(cin, line))
    {
        if(line == "")
        {
            map_index++;
            continue;
        }
        ss = stringstream(line);
        if(!isdigit(line[0]))
        {
            ss >> token;
            maps[map_index].name = token;
            continue;
        }
        int i = 0;
        range r;
        while (ss >> token)
        {
            if(i == 0)
            {
                r.dest = stoll(token);
            }
            else if(i == 1)
            {
                r.source = stoll(token);
            }
            else if(i == 2)
            {
                r.length = stoll(token);
            }
            i++;
        }
        maps[map_index].mapping.push_back(r);
    }

    unsigned long long output = get_lowest_location(maps, seeds);
    cout << output << endl;

    return;
}

int main()
{
    parse_input();
    return 0;
}

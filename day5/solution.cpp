#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;

class range
{
    public:
    unsigned long long dest;
    unsigned long long source;
    unsigned long long length;
};

class conversion_map
{
    public:
    string name;
    vector<range> mapping;
};

class seed
{
    public:
    vector<unsigned long long> dest_values; 
};

const unsigned long long dest_value(const unsigned long long& source, const range& r)
{
    unsigned long long offset = source - r.source;
    if (offset > r.length)
    {
        clog << "Offset is greater than range length" << endl;
        return 0;
    }
    return r.dest + offset;
}

bool falls_in_range(const unsigned long long& value, const range& r)
{
    if (value >= r.source && value <= r.source + r.length)
    {
        return true;
    }
    return false;
}

void traverse_maps(const vector<conversion_map>& maps, vector<seed>& seeds)
{
    for (size_t i = 0; i < seeds.size(); i++)
    {
        for (size_t j = 0; j < maps.size(); j++)
        {
            for (size_t k = 0; k < maps[j].mapping.size(); k++)
            {
                if (falls_in_range(seeds[i].dest_values[j], maps[j].mapping[k]))
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
    return;
}

seed get_lowest_location(const vector<seed>& seeds)
{
    unsigned long long lowest_location = seeds[0].dest_values[seeds[0].dest_values.size()-1];
    seed lowest_seed = seeds[0];
    for (size_t i = 0; i < seeds.size(); i++)
    {
        if (seeds[i].dest_values[seeds[i].dest_values.size()-1] < lowest_location)
        {
            lowest_location = seeds[i].dest_values[seeds[i].dest_values.size()-1];
            lowest_seed = seeds[i];
        }
    }
    return lowest_seed;
}

vector<unsigned long long> get_lowest_range(const vector<unsigned long long>& pairs, const vector<conversion_map>& maps)
{
    vector<seed> range_check_seeds;

    for (size_t i = 0; i < pairs.size(); i += 2)
    {
        unsigned long long range_start = pairs[i];
        unsigned long long range_length = pairs[i + 1];

        unsigned long long top_of_range = range_start + range_length - 1;
        unsigned long long bottom_of_range = range_start;

        seed s_top;
        s_top.dest_values.push_back(top_of_range);
        range_check_seeds.push_back(s_top);

        seed s_bottom;
        s_bottom.dest_values.push_back(bottom_of_range);
        range_check_seeds.push_back(s_bottom);
    }

    traverse_maps(maps, range_check_seeds);

    seed lowest_seed = get_lowest_location(range_check_seeds);

    vector<unsigned long long> lowest_range;
    for (size_t i = 0; i < pairs.size(); i += 2)
    {
        unsigned long long range_start = pairs[i];
        unsigned long long range_length = pairs[i + 1];

        if (range_start <= lowest_seed.dest_values[0] && lowest_seed.dest_values[0] <= range_start + range_length )
        {
            lowest_range.push_back(range_start);
            lowest_range.push_back(range_length);
        }
    }

    unsigned long long new_range_length = lowest_range[1] / 2;
    if (new_range_length < 1) { return lowest_range; }

    vector<unsigned long long> new_pairs;

    new_pairs.push_back(lowest_range[0]);
    new_pairs.push_back(new_range_length);
    new_pairs.push_back(lowest_range[0] + new_range_length + 1); // NOTE: do I need to add 1 here?
    new_pairs.push_back(new_range_length);

    return get_lowest_range(new_pairs, maps);
}

void parse_input()
{
    unsigned long long output;
    vector<conversion_map> maps; 
    for (int i = 0; i < 7; i++)
    {
        conversion_map m;
        maps.push_back(m);
    }
    
    string line;
    getline(cin, line);
    line = line.substr(7, line.length()-7);
    stringstream ss(line);

    #ifdef PART1
    vector<seed> seeds;
    string token;
    while (ss >> token)
    {
        seed s;
        s.dest_values.push_back(stoll(token));
        seeds.push_back(s);
    }
    #endif

    #ifdef PART2
    int count = 1;
    string token;
    vector<unsigned long long> pairs;
    unsigned long long range_start;
    unsigned long long range_length;
    while (ss >> token)
    {
        if (count % 2 == 1)
        {
            range_start = stoll(token);
        }
        else
        {
            range_length = stoll(token);
            pairs.push_back(range_start);
            pairs.push_back(range_length);
        }
        count++;
    }
    #endif


    int map_index = -1;
    while (getline(cin, line))
    {
        if (line == "")
        {
            map_index++;
            continue;
        }
        ss = stringstream(line);
        if (!isdigit(line[0]))
        {
            ss >> token;
            maps[map_index].name = token;
            continue;
        }
        int i = 0;
        range r;
        while (ss >> token)
        {
            if (i == 0)
            {
                r.dest = stoll(token);
            }
            else if (i == 1)
            {
                r.source = stoll(token);
            }
            else if (i == 2)
            {
                r.length = stoll(token);
            }
            i++;
        }
        maps[map_index].mapping.push_back(r);
    }

    #ifdef PART2
    vector<unsigned long long> resized_pairs;
    vector<unsigned long long> new_pairs;
    for (size_t i = 0; i < pairs.size(); i += 2)
    {

        unsigned long long range_start = pairs[i];
        unsigned long long range_length = pairs[i + 1];

        unsigned long long new_range_length = range_length / 2;

        new_pairs.push_back(range_start);
        new_pairs.push_back(new_range_length);
        new_pairs.push_back(range_start + new_range_length + 1);
        new_pairs.push_back(new_range_length);

        vector<unsigned long long> lowest_range = get_lowest_range(new_pairs, maps);

        if (lowest_range.size() != 0)
        {
            range_start = lowest_range[0];
            range_length = lowest_range[1];

            resized_pairs.push_back(range_start);
            resized_pairs.push_back(range_length);
        }

        new_pairs.clear();
    }

    vector<seed> seeds;
    seeds.clear();
    for (size_t i = 0; i < resized_pairs.size(); i += 2)
    {
        for (unsigned long long j = resized_pairs[i]; j < resized_pairs[i] + resized_pairs[i + 1]; j++)
        {
            seed s;
            s.dest_values.push_back(j);
            seeds.push_back(s);
        }
    }
    #endif

    traverse_maps(maps, seeds);
    seed lowest_seed = get_lowest_location(seeds);
    output = lowest_seed.dest_values[lowest_seed.dest_values.size()-1];

    cout << output << endl;

    return;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    parse_input();

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    clog << "Time: " << duration.count() << "ms" << endl;

    return 0;
}

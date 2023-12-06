#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <map>

using namespace std;

const vector<vector<int>> get_adjacent_indices(int i, int j)
{
    vector<vector<int>> adjacent_indices = {};
    adjacent_indices.push_back({ i - 1, j - 1 });
    adjacent_indices.push_back({ i - 1, j });
    adjacent_indices.push_back({ i - 1, j + 1 });
    adjacent_indices.push_back({ i, j - 1 });
    adjacent_indices.push_back({ i, j + 1 });
    adjacent_indices.push_back({ i + 1, j - 1 });
    adjacent_indices.push_back({ i + 1, j });
    adjacent_indices.push_back({ i + 1, j + 1 });
    return adjacent_indices;
}

void sum_gear_ratios(const vector<vector<int>>& gear_idx, const vector<map<vector<int>, int>>& nums_in_line)
{
    map<vector<int>, vector<int>> gear_parts = {};
    int sum = 0;
    for (int i = 0; i < nums_in_line.size(); i++)
    {
        for (const auto& num : nums_in_line[i])
        {
            for (int j = 0; j < gear_idx.size(); j++)
            {
                for (int k = 0; k < gear_idx[j].size(); k++)
                {
                    bool found = false;
                    vector<vector<int>> adjacent_indices = get_adjacent_indices(j, gear_idx[j][k]);
                    for (int l = 0; l < num.first.size(); l++)
                    {
                        if (found) { break; }
                        for (const auto& adjacent_index : adjacent_indices)
                        {
                            if (adjacent_index[0] == i && adjacent_index[1] == num.first[l])
                            {
                                gear_parts[{ j, gear_idx[j][k] }].push_back(num.second);
                                found = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for (const auto& gear_part : gear_parts)
    {
        if (gear_part.second.size() == 2) { sum += gear_part.second[0] * gear_part.second[1]; }
    }

    cout << sum << endl;
    return;
}

void sum_valid_nums(const vector<vector<int>>& valid_indices, const vector<map<vector<int>, int>>& nums_in_line)
{
    int sum = 0;
    for (int i = 0; i < nums_in_line.size(); i++)
    {
        for (const auto& num: nums_in_line[i])
        {
            bool valid = false;
            for (int j = 0; j < num.first.size(); j++)
            {
                if (valid) { break; }
                for (const auto& valid_index : valid_indices)
                {
                    if (valid_index[0] == i && valid_index[1] == num.first[j])
                    {
                        sum += num.second;
                        valid = true;
                        break;
                    }
                }
            }
        }
    }
    cout << sum << endl;
    return;
}


const vector<int> get_symbols_in_line(const string& line)
{
    vector<int> symbols_idx = {};

    for (int i = 0; i < line.length(); i++)
    {
        if (isdigit(line[i]) == 0 && isalpha(line[i]) == 0 && line[i] != '.')
        {
            #ifdef PART2
            if (line[i] == '*') { symbols_idx.push_back(i); }
            #endif

            #ifdef PART1
            symbols_idx.push_back(i);
            #endif
        }
    }
    return symbols_idx;
}

const map<vector<int>, int> get_nums_in_line(const string& line)
{
    map<vector<int>, int> mp;

    for (int i = 0; i < line.length(); i++)
    {
        if (isdigit(line[i]))
        {
            vector<int> idx = {};
            int j = i;
            while (j < line.length() && (j-i) <= 3 && isdigit(line[j]))
            {
                idx.push_back(j);
                j++;
            }
            mp[idx] = stoi(line.substr(i, j - i));
            i = j - 1;
        }
    }
    return mp;
}

void parse_input()
{
    vector<map<vector<int>, int>> nums_in_line;
    vector<vector<int>> symbols_idx;
    vector<vector<int>> valid_indices;

    string line;
    while (getline(cin, line))
    {
        nums_in_line.push_back(get_nums_in_line(line));
        symbols_idx.push_back(get_symbols_in_line(line));
    }

    #ifdef PART1
    for (int i = 0; i < symbols_idx.size(); i++)
    {
        for (int j = 0; j < symbols_idx[i].size(); j++)
        {
            vector<vector<int>> adjacent_indices = get_adjacent_indices(i, symbols_idx[i][j]);

            for (const auto& adjacent_index : adjacent_indices) { valid_indices.push_back(adjacent_index); }
        }
    }
    #endif

    #ifdef PART1
    sum_valid_nums(valid_indices, nums_in_line);
    #endif

    #ifdef PART2
    sum_gear_ratios(symbols_idx, nums_in_line);
    #endif

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

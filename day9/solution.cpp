#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;

class Report
{
    public:
        vector<vector<int>> history;
};

void backwards_extrapolate_history(Report& report)
{
    for (int i = report.history.size()-1; i >= 0; i--)
    {
        if ((unsigned long)i == report.history.size()-1)
        {
            report.history[i].insert(report.history[i].begin(), 0);
        }
        else
        {
            int diff = report.history[i+1][0];
            int first = report.history[i][0];
            report.history[i].insert(report.history[i].begin(), first - diff);
        }
    }
    return;
}

void extrapolate_history(Report& report)
{
    for (int i = report.history.size()-1; i >= 0; i--)
    {
        if ((unsigned long)i == report.history.size()-1)
        {
            report.history[i].push_back(0);
        }
        else
        {
            int diff = report.history[i+1][report.history[i+1].size()-1];
            int last = report.history[i][report.history[i].size()-1];
            report.history[i].push_back(diff + last);
        }
    }
    return;
}

void create_sub_histories(Report& report)
{
    vector<int> sub_history = report.history[0];
    while (true)
    {
        bool all_zero = true;
        for (size_t i = 0; i < sub_history.size(); i++)
        {
            if (sub_history[i] != 0)
            {
                all_zero = false;
            }
        }
        if (all_zero) { break; }

        vector<int> new_sub_history;
        int diff;
        for (size_t i = 0; i < sub_history.size() - 1; i++)
        {
            diff = sub_history[i + 1] - sub_history[i];
            new_sub_history.push_back(diff);
        }
        report.history.push_back(new_sub_history);
        sub_history = new_sub_history;
    }
}

void parse_input()
{
    string line;
    vector<Report> reports;
    while (getline(cin, line))
    {
        Report report;
        vector<int> history;
        stringstream ss(line);
        string token;
        while (ss >> token)
        {
            history.push_back(stoi(token));
        }
        report.history.push_back(history);
        reports.push_back(report);
    }
    for (unsigned long i = 0; i < reports.size(); i++)
    {
        create_sub_histories(reports[i]);
    }
    int output = 0;
    for (unsigned long i = 0; i < reports.size(); i++)
    {
        #ifdef PART1
        extrapolate_history(reports[i]);
        output += reports[i].history[0][reports[i].history[0].size()-1];
        #else
        backwards_extrapolate_history(reports[i]);
        output += reports[i].history[0][0];
        #endif
    }
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

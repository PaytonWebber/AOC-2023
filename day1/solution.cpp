#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int word_to_digit(string word)
{
    map<string, int> digit_map;
    digit_map["one"] = 1;
    digit_map["two"] = 2;
    digit_map["three"] = 3;
    digit_map["four"] = 4;
    digit_map["five"] = 5;
    digit_map["six"] = 6;
    digit_map["seven"] = 7;
    digit_map["eight"] = 8;
    digit_map["nine"] = 9;

    if (digit_map.find(word) != digit_map.end())
    {
        return digit_map[word];
    }
    return -1;
}

int get_calibration_value(string line)
{
    string calibration_value = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (isdigit(line[i]))
        {
            calibration_value += line[i];
            break;
        }

        #ifdef PART2
        for (int j = 3; j <= 5 && (i + j) < line.length(); j++)
        {
            int digit = word_to_digit(line.substr(i, j));
            if (digit != -1)
            {
                calibration_value += to_string(digit);
                goto backwards;
            }
        }
        #endif
    }

backwards:
    for (int i = line.length() - 1; i >= 0; i--)
    {
        if (isdigit(line[i]))
        {
            calibration_value += line[i];
            break;
        }

        #ifdef PART2
        for (int j = 3; j <= 5 && (i - j + 1) >= 0; j++)
        {
            int digit = word_to_digit(line.substr(i - j + 1, j));
            if (digit != -1)
            {
                calibration_value += to_string(digit);
                goto end;
            }
        }
        #endif
    }

end:
    return stoi(calibration_value);
}

void parse_input()
{
    int output = 0;
    string line; 
    while (getline(cin, line))
    {
        output += get_calibration_value(line);
    }
    cout << output << endl;
}

int main()
{
    parse_input();
    return 0;
}

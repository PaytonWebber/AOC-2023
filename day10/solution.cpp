#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

vector<int> get_next_pos(char curr_pipe, vector<int> curr_pos, vector<int> came_from_dir)
{
    vector<int> up = { 1, 0 };
    vector<int> down = { -1, 0 };
    vector<int> left = { 0, 1 };
    vector<int> right = { 0, -1 };

    if (came_from_dir == up)
    {
        if (curr_pipe == '|') { return { curr_pos[0]+1, curr_pos[1] }; }
        else if (curr_pipe == 'J') { return { curr_pos[0], curr_pos[1]-1 }; }
        else if (curr_pipe == 'L') { return { curr_pos[0], curr_pos[1]+1 }; }
    }
    else if (came_from_dir == down)
    {
        if (curr_pipe == '|') { return { curr_pos[0]-1, curr_pos[1] }; }
        else if (curr_pipe == '7') { return { curr_pos[0], curr_pos[1]-1 }; }
        else if (curr_pipe == 'F') { return { curr_pos[0], curr_pos[1]+1 }; }
    }
    else if (came_from_dir == left)
    {
        if (curr_pipe == '-') { return { curr_pos[0], curr_pos[1]+1 }; }
        else if (curr_pipe == 'J') { return { curr_pos[0]-1, curr_pos[1] }; }
        else if (curr_pipe == '7') { return { curr_pos[0]+1, curr_pos[1] }; }
    }
    else if (came_from_dir == right)
    {
        if (curr_pipe == '-') { return { curr_pos[0], curr_pos[1]-1 }; }
        else if (curr_pipe == 'L') { return { curr_pos[0]-1, curr_pos[1] }; }
        else if (curr_pipe == 'F') { return { curr_pos[0]+1, curr_pos[1] }; }
    }
    return {};
}

int get_longest_path(vector<string>& pipe_map)
{
    vector<int> start_pos;
    for (size_t i = 0; i < pipe_map.size(); i++)
    {
        if (find(pipe_map[i].begin(), pipe_map[i].end(), 'S') != pipe_map[i].end())
        {
            start_pos = { (int)i, (int)(find(pipe_map[i].begin(), pipe_map[i].end(), 'S') - pipe_map[i].begin()) };
            break;
        }
    }
    

    vector<int> curr_pos_a;
    vector<int> prev_pos_a;
    vector<int> curr_pos_b;
    vector<int> prev_pos_b;

    vector<int> up;
    vector<int> down;
    vector<int> left;
    vector<int> right;

    if (start_pos[0] > 0) { up = { start_pos[0] - 1, start_pos[1] }; }
    if (start_pos[0] < (int)pipe_map.size() - 1) { down = { start_pos[0] + 1, start_pos[1] }; }
    if (start_pos[1] > 0) { left = { start_pos[0], start_pos[1] - 1 }; }
    if (start_pos[1] < (int)pipe_map[0].size() - 1) { right = { start_pos[0], start_pos[1] + 1 }; }

    if (!up.empty())
    {
        char up_char = pipe_map[up[0]][up[1]];
        if (up_char == '|' || up_char == '7' || up_char == 'F')
        {
            curr_pos_a = up;
        }

    }
    if (!down.empty())
    {
        char down_char = pipe_map[down[0]][down[1]];
        if (down_char == '|' || down_char == 'L' || down_char == 'J')
        {
            if (curr_pos_a.empty())
            {
                curr_pos_a = down;
            }
            else
            {
                curr_pos_b = down;
            }
        }
    }
    if (!left.empty())
    {
        char left_char = pipe_map[left[0]][left[1]];
        if (left_char == '-' || left_char == 'L' || left_char == 'F')
        {
            if (curr_pos_a.empty())
            {
                curr_pos_a = left;
            }
            else
            {
                curr_pos_b = left;
            }
        }
    }
    if (!right.empty())
    {
        char right_char = pipe_map[right[0]][right[1]];
        if (right_char == '-' || right_char == 'J' || right_char == '7')
        {
            curr_pos_b = right;
        }
    }

    prev_pos_a = start_pos;
    prev_pos_b = start_pos;
    
    int longest_path = 1;

    char curr_char;
    vector<int> next_pos;
    vector<int> came_from_dir;
    while (curr_pos_a != curr_pos_b)
    {
        curr_char = pipe_map[curr_pos_a[0]][curr_pos_a[1]];
        came_from_dir = { curr_pos_a[0] - prev_pos_a[0], curr_pos_a[1] - prev_pos_a[1] };
        
        next_pos = get_next_pos(curr_char, curr_pos_a, came_from_dir);
        prev_pos_a = curr_pos_a;
        curr_pos_a = next_pos;

        curr_char = pipe_map[curr_pos_b[0]][curr_pos_b[1]];
        came_from_dir = { curr_pos_b[0] - prev_pos_b[0], curr_pos_b[1] - prev_pos_b[1] };

        next_pos = get_next_pos(curr_char, curr_pos_b, came_from_dir);
        prev_pos_b = curr_pos_b;
        curr_pos_b = next_pos;

        longest_path++;
    }
    return longest_path;
}

void parse_input()
{
    vector<string> pipe_map;

    string line;
    while (getline(cin, line)) { pipe_map.push_back(line); }

    int longest_path = get_longest_path(pipe_map);
    cout << longest_path << endl;
    return;
}

int main()
{
    parse_input();
    return 0;
}

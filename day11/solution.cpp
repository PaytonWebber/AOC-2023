#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

class Node
{
    public:
        int row;
        int col;
        int dist;
        Node(int x, int y, int w): row(x), col(y), dist(w) {}
};

class Pair
{
    public:
        vector<int> start;
        vector<int> end;
        int dist;
        Pair(vector<int> s, vector<int> e): start(s), end(e) {}
};

int min_distance(vector<string>& universe, vector<int> start, vector<int> end)
{
    Node s(start[0], start[1], 0);

    vector<vector<int>> visited((int)universe.size(), vector<int>((int)universe[0].size(), 0));
    visited[s.row][s.col] = 1;
    queue<Node> q;
    q.push(s);

    while(!q.empty())
    {
        Node p = q.front();
        q.pop();

        // found end
        if (p.row == end[0] && p.col == end[1]) { return p.dist; }

        // move up
        if (p.row - 1 >= 0 && visited[p.row-1][p.col] == 0)
        {
            q.push(Node(p.row - 1, p.col, p.dist + 1));
            visited[p.row-1][p.col] = 1;
        }

        // move down
        if (p.row + 1 < (int)universe.size() && visited[p.row+1][p.col] == 0)
        {
            q.push(Node(p.row + 1, p.col, p.dist + 1));
            visited[p.row+1][p.col] = 1;
        }

        // move left
        if (p.col - 1 >= 0 && visited[p.row][p.col-1] == 0)
        {
            q.push(Node(p.row, p.col - 1, p.dist + 1));
            visited[p.row][p.col-1] = 1;
        }

        // move right
        if (p.row + 1 < (int)universe[0].size() && visited[p.row][p.col+1] == 0)
        {
            q.push(Node(p.row, p.col + 1, p.dist + 1));
            visited[p.row][p.col+1] = 1;
        }
    }

    return -1;
}

vector<Pair> create_pairs(vector<vector<int>> positions)
{
    vector<Pair> pairs;

    for (int i = 0; i < (int)positions.size(); i++)
    {
        for (int j = i + 1; j < (int)positions.size(); j++)
        {
                Pair p(positions[i], positions[j]);
                pairs.push_back(p);
        }
    }
    return pairs;
}

vector<vector<int>> get_galaxies_positions(vector<string>& universe)
{
    vector<vector<int>> galaxies;
    
    for (int i = 0; i < (int)universe.size(); i++)
    {
        for (int j = 0; j < (int)universe[i].size(); j++)
        {
            if (universe[i][j] == '#') { galaxies.push_back({ i, j }); }
        }
    }

    return galaxies;
}

vector<string> transpose_universe(vector<string>& universe)
{
    vector<string> transposed_universe;
    for (int i = 0; i < (int)universe[0].size(); i++)
    {
        string transposed_line = "";
        for (int j = 0; j < (int)universe.size(); j++)
        {
            transposed_line += universe[j][i];
        }
        transposed_universe.push_back(transposed_line);
    }
    return transposed_universe;
}

vector<string> expand_universe(vector<string>& universe)
{
    vector<string> expanded_universe;

    for (auto& line : universe)
    {
        if (find(line.begin(), line.end(), '#') == line.end())
        {
            expanded_universe.push_back(line);
        }
        expanded_universe.push_back(line);
    }

    return expanded_universe;
}

void parse_input()
{
    vector<string> og_universe;
    string line;
    while (getline(cin, line)) { og_universe.push_back(line); }

    vector<string> rows_expanded = expand_universe(og_universe);
    vector<string> transpose_rows = transpose_universe(rows_expanded);

    vector<string> columns_expanded = expand_universe(transpose_rows);
    vector<string> expanded_universe = transpose_universe(columns_expanded);

    vector<vector<int>> galaxies_positions = get_galaxies_positions(expanded_universe);

    vector<Pair> pairs = create_pairs(galaxies_positions);

    int sum_shortest_paths = 0;
    int num_pairs = (int)pairs.size();
    for (int i = 0; i < num_pairs; i++)
    {
        clog << "\rchecking: " << i << " of " << num_pairs << flush;
        int shortest_path = min_distance(expanded_universe, pairs[i].start, pairs[i].end);
        pairs[i].dist = shortest_path;
        sum_shortest_paths += shortest_path;
    }
    cout << endl;
    cout << sum_shortest_paths << endl;

    return;
}

int main()
{
    parse_input();
    return 0;
}

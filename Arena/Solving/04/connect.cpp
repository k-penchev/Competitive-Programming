#include <bits/stdc++.h>

const int mxN = 1e5 + 5;
std::set<int> g[mxN];

void initialize(int ID, int N, int M, int Q, std::vector<std::pair<int, int>> friendships)
{
    for(auto& p : friendships)
    {
        int from = p.first;
        int to = p.second;
        g[from].insert(to);
        g[to].insert(from);
    }
}

void connect(int ID, int x, int y)
{
    g[x].insert(y);
    g[y].insert(x);
}

bool question(int ID, int x, int y)
{
    for(auto it = g[x].begin() ; it != g[x].end() ; ++it)
    {
        if(g[y].find(*it) != g[y].end())
        {
            return true;
        }
    }
    
    return false;
}
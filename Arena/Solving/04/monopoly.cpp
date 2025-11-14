#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 5 * 1e5 + 10;
const int MAXM = 2 * 1e6 + 10;

int n, m;

struct Edge
{
    int to;
    int idx;
};

std::vector<Edge> g[MAXN];
bool flip[MAXM];
int in[MAXN], out[MAXN];
int timer = 0;

void dfs(int node)
{
    in[node] = ++timer;

    for(auto &[to, idx] : g[node])
    {
        if(in[to] == 0)
        {
            dfs(to);
        }
        else if(out[to] == 0)
        {
            flip[idx] = 1;
        }
    }

    out[node] = ++timer;
}

std::string find_reverse(int N, int M, int connections[][2])
{
    n = N;
    m = M;

    for(int i = 0 ; i < m ; ++i)
    {
        int a = connections[i][0];
        int b = connections[i][1];
        g[a].push_back({b, i});
    }

    for(int i = 0 ; i < n ; ++i)
    {
        if(in[i] == 0)
        {
            dfs(i);
        }
    }
    
    std::string res;
    for(int i = 0 ; i < m ; ++i)
    {
        char c = (flip[i] ? '1' : '0');
        res.push_back(c);
    }

    return res;
}

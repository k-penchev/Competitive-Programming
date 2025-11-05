//the graph is known in advance
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, m;
std::vector<int> g[MAXN];
bool visited[MAXN];

std::vector<std::pair<int, int>> bridges;
int in[MAXN], low[MAXN];
int timer = 1;

void dfs(int node, int parent)
{
    visited[node] = 1;
    in[node] = low[node] = timer++;

    bool skippedParent = false; //needed, because we can have multi-edge
    for(int to : g[node])
    {
        if(to == parent && !skippedParent)
        {
            skippedParent = 1;
            continue;
        }

        if(visited[to]) //back edge
        {
            low[node] = std::min(low[node], in[to]);
        }
        else
        {
            dfs(to, node);

            low[node] = std::min(low[node], low[to]);

            if(low[to] > in[node])
            {
                bridges.push_back({node, to});
            }
        }
    }
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    for(auto &x : bridges)
    {
        std::cout << x.first << " " << x.second << "\n";
    }
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
    
    return 0;
}
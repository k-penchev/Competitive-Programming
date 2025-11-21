#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 10000 + 10;
const int MAXM = 100000 + 10;

int n, m;

struct Edge
{
    int to;
    int idx;
};

std::vector<Edge> g[MAXN];
bool visited[MAXN];
int depth[MAXN], low[MAXN];
int timer = 1;

bool isBridge[MAXM];
bool isPoint[MAXN];

void dfs(int node, int parent)
{
    visited[node] = 1;
    depth[node] = low[node] = timer++;

    int cnt = 0;
    bool skippedParent = false;
    for(auto &[to, edge] : g[node])
    {
        if(to == parent && !skippedParent)
        {
            skippedParent = 1;
            continue;
        }

        if(visited[to])
        {
            low[node] = std::min(low[node], depth[to]);
        }
        else
        {
            dfs(to, node);
            low[node] = std::min(low[node], low[to]);

            if(low[to] > depth[node])
            {
                isBridge[edge] = 1;
            }

            if(low[to] >= depth[node] && parent != -1)
            {
                isPoint[node] = 1;
            }

            cnt += 1;
        }
    }

    if(parent == -1 && cnt > 1)
    {
        isPoint[node] = 1;
    }
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    dfs(1, -1);

    std::vector<int> bridges;
    std::vector<int> points;

    for(int i = 1 ; i <= m ; ++i)
    {
        if(isBridge[i])
        {
            bridges.push_back(i);
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(isPoint[i])
        {
            points.push_back(i);
        }
    }

    std::cout << bridges.size() << "\n";
    for(int x : bridges) std::cout << x << "\n";

    std::cout << points.size() << "\n";
    for(int x : points) std::cout << x << "\n";
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
}
#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 500 + 10;
const int INF = 1e18 + 10;

int n, m, q;

struct Edge
{
    int a;
    int b;
    int w;
};

std::vector<Edge> edges;
int dist[MAXN][MAXN];

bool hasCycle;

void floyd_warshall()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            dist[i][j] = INF;
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        dist[i][i] = 0;
    }

    for(auto &[a, b, w] : edges)
    {
        dist[a][b] = dist[b][a] = std::min(dist[a][b], w);
    }

    for(int k = 1 ; k <= n ; ++k)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            for(int j = 1 ; j <= n ; ++j)
            {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    hasCycle = false;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(dist[i][i] < 0)
        {
            hasCycle = true;
        }
    }

    for(int k = 1 ; k <= n ; ++k)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            for(int j = 1 ; j <= n ; ++j)
            {
                if(dist[i][k] < INF && dist[k][k] < 0 && dist[k][j] < INF)
                {
                    //The path from i to j passes through a negative cycle
                    dist[i][j] = -INF;
                }
            }
        }
    }
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    floyd_warshall();
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
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
}

void solve()
{
    std::cin >> n >> m >> q;

    for(int i = 1 ; i <= m ; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    floyd_warshall();

    for(int i = 1 ; i <= q ; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        std::cout << (dist[u][v] != INF ? dist[u][v] : -1) << "\n";
    }
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
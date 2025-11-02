#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int INF = 1e9 + 10;

int n, m;

struct Edge
{
    int from, to;
    int w;
};

std::vector<Edge> edges;
int dist[MAXN];

void bellman_ford(int source)
{
    std::fill(dist + 1, dist + n + 1, INF);
    dist[source] = 0;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        for(auto& [u, v, w] : edges)
        {
            dist[v] = std::min(dist[v], dist[u] + w);
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

    bellman_ford(1);

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << dist[i] << " ";
    }

    std::cout << "\n";
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
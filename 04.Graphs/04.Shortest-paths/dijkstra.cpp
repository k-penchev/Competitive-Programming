#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define int long long

const int MAXN = 1e5 + 10;
const int INF = 1e18 + 10;

int n, m;
std::vector<std::pair<int, int>> g[MAXN];
int dist[MAXN];

void dijkstra(int source)
{
    std::priority_queue<std::pair<int, int>> pq;
    std::fill(dist + 1, dist + n + 1, INF);

    pq.push({0, source});
    dist[source] = 0;

    while(pq.size())
    {
        int currentDist = -pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if(currentDist > dist[currentNode]) continue;

        for(auto& [to, w] : g[currentNode])
        {
            if(dist[currentNode] + w < dist[to])
            {
                dist[to] = dist[currentNode] + w;
                pq.push({-dist[to], to});
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
        g[u].push_back({v, w});
    }

    dijkstra(1);

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

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
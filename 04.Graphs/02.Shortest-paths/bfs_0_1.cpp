#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <deque>

#define int long long

const int MAXN = 1e5 + 10;
const int INF = 1e18 + 10;

int n, m;
std::vector<std::pair<int, int>> g[MAXN];
int dist[MAXN];

void bfs_0_1(int source)
{
    std::deque<int> q;
    std::fill(dist + 1, dist + n + 1, INF);

    q.push_front(source);
    dist[source] = 0;

    while(q.size())
    {
        int currentNode = q.front();
        q.pop_front();

        for(auto& [to, w] : g[currentNode])
        {
            if(dist[currentNode] + w < dist[to])
            {
                dist[to] = dist[currentNode] + w;

                if(w == 0)
                {
                    q.push_front(to);
                }
                else
                {
                    q.push_back(to);
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

        assert(w == 0 || w == 1);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    bfs_0_1(1);

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
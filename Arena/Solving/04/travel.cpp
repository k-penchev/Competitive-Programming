#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int MAXN = 80 + 10;
const int INF = 1e9;

int n, m;

struct Node
{
    int to;
    int w;
    int idx;
};

std::vector<Node> g[MAXN];
int dist[MAXN];
std::pair<int, int> par[MAXN];
std::priority_queue<std::pair<int, int>> pq;
std::vector<int> edges;

void dijkstra(int source, int destination)
{
    std::fill(dist + 1, dist + n + 1, INF);

    for(int i = 1 ; i <= n ; ++i)
    {
        par[i] = {-1, -1};
    }

    pq.push({0, source});
    dist[source] = 0;

    while(pq.size())
    {
        int curr_node = pq.top().second;
        int curr_dist = -pq.top().first;
        pq.pop();

        if(curr_dist > dist[curr_node]) continue;

        for(auto& [to, w, idx] : g[curr_node])
        {
            if(dist[curr_node] + w < dist[to])
            {
                dist[to] = dist[curr_node] + w;
                par[to] = {curr_node, idx};

                pq.push({-dist[to], to});
            }
        }
    }

    int final_dist = dist[destination], cnt_edges = 0;

    while(destination != -1)
    {
        auto [prev, idx] = par[destination];
        
        if(idx != -1)
        {
            cnt_edges += 1;
            edges.push_back(idx);
        }

        destination = prev;
    }

    std::cout << final_dist << " " << cnt_edges << "\n";

    std::reverse(edges.begin(), edges.end());
    for(int edge : edges)
    {
        std::cout << edge << " " << "1" << "\n";
    }

    std::cout << "\n";
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
    {
        int x;
        std::cin >> x;
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].push_back({v, w, i});
    }

    dijkstra(1, n);
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
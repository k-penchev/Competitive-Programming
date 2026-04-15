#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 1000 + 10;
const int INF = 1e9 + 10;

int n, m;
struct Edge
{
    int to;
    int flow;
    int cap;
    int cost;
    int backEdge;
};

int source, sink;
std::vector<Edge> g[MAXN];
int prevNode[MAXN];
int prevEdge[MAXN];
int dist[MAXN];

bool bellman_ford()
{
    std::fill(dist + 1, dist + n + 1, INF);
    dist[source] = 0;

    for(int iter = 1 ; iter <= n - 1 ; ++iter)
    {
        bool updated = false;

        for(int node = 1 ; node <= n ; ++node)
        {
            if(dist[node] == INF)
            {
                continue;
            }

            for(int i = 0 ; i < (int)g[node].size() ; ++i)
            {
                auto &[to, flow, cap, cost, backEdge] = g[node][i];

                if(flow == cap)
                {
                    continue;
                }

                if(dist[node] + cost < dist[to])
                {
                    dist[to] = dist[node] + cost;
                    prevNode[to] = node;
                    prevEdge[to] = i;
                    updated = true;
                }
            }
        }

        if(!updated)
        {
            break;
        }
    }

    return dist[sink] != INF;
}

int edmonds_karp(int k)
{
    int totalCost = 0;
    int totalFlow = 0;

    while(totalFlow < k && bellman_ford())
    {
        int push = k - totalFlow;
        
        int curr = sink;
        while(curr != source)
        {
            auto &e = g[prevNode[curr]][prevEdge[curr]];
            push = std::min(push, e.cap - e.flow);
            curr = prevNode[curr];
        }

        curr = sink;
        while(curr != source)
        {
            auto &e = g[prevNode[curr]][prevEdge[curr]];
            e.flow += push;
            g[curr][e.backEdge].flow -= push;
            curr = prevNode[curr];
        }

        totalFlow += push;
        totalCost += push * dist[sink];
    }

    return totalCost;
}

void addEdge(int a, int b, int capacity, int cost)
{
    g[a].push_back({b, 0, capacity, cost, (int)g[b].size()});
    g[b].push_back({a, 0, 0, -cost, (int)g[a].size() - 1});
}

void solve()
{
   std::cin >> n >> m;
    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, cost;
        std::cin >> a >> b >> cost;
        addEdge(a, b, 1, cost);
        addEdge(b, a, 1, cost);
    } 

    source = 1, sink = n;
    std::cout << edmonds_karp(2) << "\n";
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
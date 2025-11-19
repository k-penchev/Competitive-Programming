#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 2500 + 10;
const int INF = 1e9 + 10;

int n, m;

struct Edge
{
    int a;
    int b;
    int w;
};

std::vector<Edge> edges;
int dist[MAXN];
int parent[MAXN];

void bellman_ford()
{
    //imagine we have a super source
    std::fill(parent + 1, parent + n + 1, -1);
    std::fill(dist + 1, dist + n + 1, 0);

    int node;
    for(int i = 1 ; i <= n ; ++i) //n iterations , not n - 1
    {
        node = -1;
        for(auto &[a, b, w] : edges)
        {
            if(dist[a] + w < dist[b])
            {
                dist[b] = std::max(-INF, dist[a] + w);
                parent[b] = a;
                node = b;
            }
        }
    }

    if(node == -1)
    {
        std::cout << "NO" << "\n";
        return;
    }
    
    for(int i = 1 ; i <= n ; ++i)
    {
        node = parent[node];
    }

    std::vector<int> cycle;
    for(int v = node ; ; v = parent[v])
    {
        cycle.push_back(v);

        if(v == node && cycle.size() > 1)
        {
            break;
        }
    }

    std::reverse(cycle.begin(), cycle.end());

    std::cout << "YES" << "\n";
    for(int &x : cycle)
    {
        std::cout << x << " ";
    }

    std::cout << "\n";
}

void solve()
{
    std::cin >> n >> m;
    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, w;
        std::cin >> a >> b >> w;
        edges.push_back({a, b, w});
    }

    bellman_ford();
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
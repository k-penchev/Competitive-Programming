#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int INF = 1e18 + 10;

int n, m;

struct Edge
{
    int from;
    int to;
    int x;
    int y;
};

struct DSU
{
    int parent[MAXN];
    int size[MAXN];

    void set()
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x)
    {
        if(parent[x] == x)
        {
            return x;
        }

        return parent[x] = find(parent[x]);
    }

    void connect(int x, int y)
    {
        x = find(x);
        y = find(y);

        if(x == y)
        {
            return;
        }

        if(size[x] > size[y])
        {
            std::swap(x, y);
        }

        parent[x] = y;
        size[y] += size[x];
    }

    bool areConnected(int x, int y)
    {
        return find(x) == find(y);
    }
};

std::vector<Edge> graph[MAXN];
std::vector<Edge> edges;
DSU dsu;
int maxEdge;
int minDist;
int dist[MAXN];

void dijkstra(int source, int destination)
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

        for(auto& [from, to, x, y] : graph[currentNode])
        {
            if(dist[currentNode] + y <= dist[to])
            {
                dist[to] = dist[currentNode] + y;
                pq.push({-dist[to], to});
            }
        }
    }

    minDist = dist[destination];
}

void calculateMax(int source, int destination)
{
    std::sort(edges.begin(), edges.end(), [&](const Edge& a, const Edge& b)
    {
        return a.x < b.x;
    });

    dsu.set();

    for(auto& [from, to, x, y] : edges)
    {
        if(!dsu.areConnected(from, to))
        {
            dsu.connect(from, to);

            if(dsu.areConnected(source, destination))
            {
                maxEdge = x;
                break;
            }
        }
    }

    for(auto& [from, to, x, y] : edges)
    {
        if(x <= maxEdge)
        {
            graph[from].push_back({-1, to, x, y});
            graph[to].push_back({-1, from, x, y});
        }
    }
}

void solve()
{
    std::cin >> n >> m;
    
    for(int i = 1 ; i <= m ; ++i)
    {
        int u, v, x, y;
        std::cin >> u >> v >> x >> y;
        edges.push_back({u, v, x, y});
    }
    
    calculateMax(1, n);
    dijkstra(1, n);

    std::cout << maxEdge << " " << minDist << "\n";
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
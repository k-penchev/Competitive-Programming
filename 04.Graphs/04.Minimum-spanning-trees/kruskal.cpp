#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, m;

struct Edge
{
    int from, to;
    int w;
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

DSU dsu;
std::vector<Edge> edges;
long long mstWeight;

void findMST()
{
    std::sort(edges.begin(), edges.end(), [&](const Edge& a, const Edge& b)
    {
        return a.w < b.w;
    });

    dsu.set();

    int cnt = 0;

    for(auto& [from, to, w] : edges)
    {
        if(cnt == n - 1)
        {
            break;
        }

        if(!dsu.areConnected(from, to))
        {
            dsu.connect(from, to);
            mstWeight += w;
            cnt += 1;
        }
    }

    if(cnt == n - 1) std::cout << mstWeight << "\n";
    else std::cout << "IMPOSSIBLE" << "\n";
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

    findMST();    
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
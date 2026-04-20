#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 2 * 1e5 + 10;

int n, m;

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

DSU dsu;

void solve()
{
    std::cin >> n >> m;
    
    dsu.set();
    for(int i = 1 ; i <= m ; ++i)
    {
        int type, x, y;
        std::cin >> type >> x >> y;

        if(type == 0) //connect two nodes
        {
            dsu.connect(x, y);
        }
        else //check if two nodes are connected
        {
            std::cout << dsu.areConnected(x, y) << "\n";
        }
    }
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
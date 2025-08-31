#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, m, q;

struct Edge
{
    int a;
    int b;
    int w;
};

vector<Edge> edges;

struct DSU
{
    int par[MAXN], sz[MAXN];

    void set()
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x)
    {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY)
        {
            if(sz[rootX] < sz[rootY])
            {
                par[rootX] = rootY;
                sz[rootY] += sz[rootX];
            }
            else
            {
                par[rootY] = rootX;
                sz[rootX] += sz[rootY];
            }
        }
    }

    bool areConnected(int x, int y)
    {
        return (find(x) == find(y));
    }
};

DSU dsu;

void init()
{
    dsu.set();


}

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({a, b, w});
    }

    init();

    cin >> q;

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int a, b; cin >> a >> b;
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
    
    return 0;
}
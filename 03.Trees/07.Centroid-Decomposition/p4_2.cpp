#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 2 * 1e5 + 10;
const int INF = 1e9;

int n, k1, k2;
std::vector<int> tree[MAXN];
long long globalAns = 0;

namespace Fenwick
{
    int bit[MAXN];

    void update(int idx, int val)
    {
        idx++;

        for ( ; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] += val;
        }
    }

    int query(int l, int r) // 0 - based
    {
        ++r;

        int s = 0;
        
        for ( ; r >= 1 ; r -= (r & (-r)))
        {
            s += bit[r];
        }

        for ( ; l >= 1 ; l -= (l & (-l)))
        {
            s -= bit[l];
        }

        return s;
    }
};

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    int maxDepth = 0;

    void findSize(int node, int par)
    {   
        sz[node] = 1;

        for (const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;

            findSize(child, node);
            sz[node] += sz[child];
        }
    }

    int getCentroid(int node, int par, int globalSize)
    {
        for (const int& child : tree[node])
        {
            if(child == par || vis[child] || sz[child] * 2 <= globalSize) continue;
            return getCentroid(child, node, globalSize);
        }
        return node;
    }

    void computePaths(int node, int par, int currDepth, bool filling)
    {
        if(currDepth > k2) return;
        maxDepth = std::max(maxDepth, currDepth);

        if(filling)
        {
            Fenwick::update(currDepth, +1);
        }
        else
        {
            globalAns += Fenwick::query(std::max(0, k1 - currDepth), k2 - currDepth);
        }

        for (const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;
            computePaths(child, node, currDepth + 1, filling);
        }
    }

    void decompose(int node)
    {
        findSize(node, 0);
        int cntr = getCentroid(node, 0, sz[node]);

        vis[cntr] = true;
        maxDepth = 0;



        for (const int& child : tree[cntr])
        {
            if(vis[child]) continue;

            computePaths(child, cntr, 1, false);
            computePaths(child, cntr, 1, true);
        }

        for(int i = 1 ; i <= maxDepth ; ++i)
        {
            Fenwick::update(i, -Fenwick::query(i, i));
        }

        for (const int& child : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child);
        }
    }

    void build()
    {
        Fenwick::update(0, +1);
        decompose(1);
    }
};

void solve()
{
    std::cin >> n >> k1 >> k2;

    for (int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        std::cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    Centroid::build();
    std::cout << globalAns << "\n";
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
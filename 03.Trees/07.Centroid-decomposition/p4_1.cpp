#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 2 * 1e5 + 10;
const int INF = 1e9;

int n, k;
std::vector<int> tree[MAXN];
long long globalAns = 0;

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    int cnt[MAXN];
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
        if(currDepth > k) return;

        maxDepth = std::max(maxDepth, currDepth);

        if(filling)
        {
            cnt[currDepth]++;
        }
        else
        {
            globalAns += cnt[k - currDepth];
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

        cnt[0] = 1;
        for (const int& child : tree[cntr])
        {
            if(vis[child]) continue;

            computePaths(child, cntr, 1, false);
            computePaths(child, cntr, 1, true);
        }

        cnt[0] = 0;                 
        std::fill(cnt + 1, cnt + maxDepth + 1, 0);

        for (const int& child : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child);
        }
    }

    void build()
    {
        std::fill(cnt, cnt + MAXN, 0);
        decompose(1);
    }
};

void solve()
{
    std::cin >> n >> k;

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
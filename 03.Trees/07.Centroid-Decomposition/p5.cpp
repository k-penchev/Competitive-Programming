#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

const int MAXN = 1e5 + 10;

int n;
std::vector<std::pair<int, int>> tree[MAXN];

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    std::unordered_map<int, int> map1, map2, map3; //many times, one time, current

    void findSize(int node, int par)
    {
        sz[node] = 1;

        for (const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;

            findSize(child, node);
            sz[node] += sz[child];
        } 
    }

    int findCentroid(int node, int par, int globalSize)
    {
        for (const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;

            if(sz[child] * 2 > globalSize) return findCentroid(child, node, globalSize);
        }

        return node;
    }

    void dfs(int node, int par, int currDist)
    {
        //map3[currDist] += 1;

        if(map1.count(-currDist)) //typeA
        {
            
        }
        else if(map2.count(currDist)) //typeB
        {

        }
        else
        {

        }

        for (const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;
            dfs(child, node, currDist + w);
        }
    }

    void decompose(int node)
    {
        findSize(node, 0);
        int cntr = findCentroid(node, 0, sz[node]);

        vis[cntr] = 1;

        for (const auto& [child, w] : tree[cntr])
        {
            if(vis[child]) continue;

            dfs(child, cntr, w);
            dfs(child, cntr, w);
        }

        for (const auto& [child, w] : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child);
        }
    }

    void build()
    {
        decompose(1);
    }
};

void solve()
{
    std::cin >> n;

    for (int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b, w;
        std::cin >> a >> b >> w;

        if (w == 0) w = -1;
        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
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
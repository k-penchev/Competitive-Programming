#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

const int MAXN = 1e5 + 10;

int n;
std::vector<std::pair<int, int>> tree[MAXN];
long long globalAnswer = 0;

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    std::unordered_map<int, int> current;
    std::unordered_map<int, int> merged;

    void findSize(int node, int par)
    {
        sz[node] = 1;

        for (const auto& [child, w] : tree[node])
        {
            if (child == par || vis[child]) continue;

            findSize(child, node);
            sz[node] += sz[child];
        }
    }

    int getCentroid(int node, int par, int globalSize)
    {
        for (const auto& [child, w] : tree[node])
        {
            if (child == par || vis[child] || 2 * sz[child] <= globalSize) continue;
            return getCentroid(child, node, globalSize);
        }

        return node;
    }

    void computeDfs(int node, int par, int currLength)
    {
        current[currLength]++;

        for (const auto& [child, w] : tree[node])
        {
            if (child == par || vis[child]) continue;
            computeDfs(child, node, currLength + w);
        }
    }

    void decompose(int node)
    {
        findSize(node, 0);
        int cntr = getCentroid(node, 0, sz[node]);

        vis[cntr] = true;

        for (const auto& [child, w] : tree[cntr])
        {
            if (vis[child]) continue;

            current.clear();
            computeDfs(child, cntr, w);

            for(auto& [dist, cnt] : current)
            {
                globalAnswer += cnt * merged[-dist];
                merged[dist] += cnt;
            }
        }

        merged.clear();

        for (const auto& [child, w] : tree[cntr])
        {
            if (vis[child]) continue;
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
    //std::freopen("yinyang.in", "r", stdin);
    //std::freopen("yinyang.out", "w", stdout);

    std::cin >> n;

    for (int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b, w;
        std::cin >> a >> b >> w;

        if (w == 0) w = -1;

        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
    }

    Centroid::build();
    std::cout << globalAnswer << "\n";
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
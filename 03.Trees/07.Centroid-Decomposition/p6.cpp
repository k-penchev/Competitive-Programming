#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long

const int MAXN = 2 * 1e5 + 10;
const int MAXK = 1e6 + 10;
const int INF = MAXN;

int n, k;
vector<vector<pair<int, int>>> tree(MAXN);
int globalAns = INF;

namespace Centroid
{
    int sz[MAXN], best[MAXK];
    bool vis[MAXN];
    int maxW = 0;

    void findSize(int node, int par)
    {
        sz[node] = 1;

        for(const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;
            
            findSize(child, node);
            sz[node] += sz[child];
        }
    }

    int getCentroid(int node, int par, int globalSize)
    {
        for(const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;

            if(sz[child] * 2 > globalSize) return getCentroid(child, node, globalSize);
        }

        return node;
    }

    void computeDist(int node, int par, int currDepth, int currWeight, bool filling)
    {
        if(currWeight > k) return;
        maxW = max(maxW, currWeight);

        if(filling)
        {
            best[currWeight] = min(best[currWeight], currDepth);
        }
        else
        {
            globalAns = min(globalAns, currDepth + best[k - currWeight]);
        }

        for(const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;
            computeDist(child, node, currDepth + 1, currWeight + w, filling);
        }
    }

    void decompose(int node)
    {
        findSize(node, 0);
        int cntr = getCentroid(node, 0, sz[node]);

        vis[cntr] = 1;
        maxW = 0;
        
        best[0] = 0;
        for(const auto& [child, w] : tree[cntr])
        {
            if(vis[child]) continue;
            
            computeDist(child, cntr, 1, w, false);
            computeDist(child, cntr, 1, w, true);
        }

        fill(best, best + min(k, maxW) + 1, INF);

        for(const auto& [child, w] : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child);
        }
    }

    void build()
    {  
        fill(best, best + MAXK, INF);
        decompose(1);
    }
};

int best_path(int N, int K, int H[][2], int L[])
{
    n = N;
    k = K;

    for(int i = 0 ; i < n - 1 ; ++i)
    {
        int a = H[i][0], b = H[i][1], w = L[i];

        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
    }

    Centroid::build();
    return (globalAns != INF ? (int)globalAns : -1);
};


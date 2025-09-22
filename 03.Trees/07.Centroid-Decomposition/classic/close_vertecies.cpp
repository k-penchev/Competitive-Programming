#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

const int MAXN = 1e5 + 10;

struct Node
{
    int l;
    int w;
    int id;
};

int n, l, w;
vector<pair<int, int>> tree[MAXN];
int ans = 0;



namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];

    void findSize(int node, int par)
    {

    }

    int findCentroid(int node, int par, int globalSize)
    {

    }

    void dfs(int node, int par, int currL, int currW, bool filling)
    {
        if(filling)
        {

        }
        else
        { 

        }

        for(const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;
            dfs(child, node, currL + 1, currW + w, filling);
        }
    }

    void decompose(int node)
    {
        findSize(node, 0);
        int cntr = findCentroid(node, 0, sz[node]);

        vis[cntr] = 1;

        for(const auto& [child, w] : tree[cntr])
        {
            if(vis[child]) continue;

            dfs(child, cntr, 1, w, false);
            dfs(child, cntr, 1, w, false);
        }

        for(const auto& [child, w] : tree[cntr])
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
    cin >> n >> l >> w;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int parent, weight;
        cin >> parent >> weight;
        tree[parent].push_back({i + 1, weight});
        tree[i + 1].push_back({parent, weight});
    }

    Centroid::build();
    cout << ans << "\n";
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
}
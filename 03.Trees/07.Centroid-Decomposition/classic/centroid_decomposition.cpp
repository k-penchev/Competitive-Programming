#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
vector<int> tree[MAXN];

namespace Centroid
{
    int siz[MAXN];
    bool is_removed[MAXN];
    vector<int> c[MAXN];

    void find_subtree_size(int node, int par)
    {
        siz[node] = 1;

        for(const int& child : tree[node])
        {
            if(child == par || is_removed[child]) continue;

            find_subtree_size(child, node);

            siz[node] += siz[child];
        }
    }

    int find_centroid(int node, int par, int root_sz)
    {
        for(const int& child : tree[node])
        {
            if(child == par || is_removed[child]) continue;

            if(siz[child] * 2 > root_sz) return find_centroid(child, node, root_sz);
        }

        return node;
    }

    int decompose(int node)
    {
        find_subtree_size(node, 0);
        int centroid = find_centroid(node, 0, siz[node]);

        is_removed[centroid] = true;

        for(const int& child : tree[centroid])
        {
            if(is_removed[child]) continue;
            c[centroid].push_back(decompose(child));
        }

        return centroid;
    }

    void dfs(int centroid, int par)
    {
        for(const int& child : c[centroid])
        {
            if(child == par) continue;
            dfs(child, centroid);
        }
    }

    void build()
    {
        int root = decompose(1);
        dfs(root, 0);
    }
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    Centroid::build();
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
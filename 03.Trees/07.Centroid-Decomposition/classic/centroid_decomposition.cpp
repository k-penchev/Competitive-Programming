#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);

namespace CD
{
    int siz[MAXN];
    bool is_removed[MAXN];

    void find_subtree_siz(int node, int par)
    {
        siz[node] = 1;
        
        for(const int& child : tree[node])
        {
            if(child == par || is_removed[child]) continue;

            find_subtree_siz(child, node);
            siz[node] += siz[child];
        }
    }

    int find_centroid(int node, int par, int sz)
    {
        for(const int& child : tree[node])
        {
            if(child == par || is_removed[child]) continue;

            if(siz[child] * 2 > sz) return find_centroid(child, node, sz);
        }

        return node;
    }

    void build(int node = 1)
    {
        //cout << "Building for " << node << "\n";
        fill(siz, siz + MAXN, 0);

        find_subtree_siz(node, 0);
        //cout << "Siz =" << siz[node] << "\n";
        int centroid = find_centroid(node, 0, siz[node]);
        //cout << "Centroid =" << centroid << "\n";
        //do something

        is_removed[centroid] = true;

        for(const int& child : tree[node])
        {
            if(is_removed[child]) continue;
            build(child);
        }
    }
};

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    CD::build();
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
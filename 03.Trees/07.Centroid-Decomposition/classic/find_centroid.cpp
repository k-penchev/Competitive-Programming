#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);

namespace CD
{
    int centroid;
    int siz[MAXN];

    void dfs1(int node, int par)
    {
        siz[node] = 1;

        for(const int& child : tree[node])
        {
            if(child == par) continue;

            dfs1(child, node);
            siz[node] += siz[child];
        }
    }

    int dfs2(int node, int par)
    {
        for(const int& child : tree[node])
        {
            if(child == par) continue;

            if(siz[child] * 2 > n) 
            {
                return dfs2(child, node);
            }
        }

        return node;
    }

    void build()
    {
        dfs1(1, 0);
        centroid = dfs2(1, 0);
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
    cout << CD::centroid << "\n";
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
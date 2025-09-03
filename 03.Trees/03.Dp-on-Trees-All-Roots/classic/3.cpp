#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
long long siz[MAXN], depth[MAXN], ans[MAXN];

void dfs2(int node, int par)
{
    for(int& child : tree[node])
    {
        if(child == par) continue;

        ans[child] = ans[node] + n - 2 * siz[child];

        dfs2(child, node);

    }
}

void dfs1(int node, int par, int currDepth)
{
    siz[node] = 1;
    ans[1] += currDepth;
    depth[node] = currDepth;

    for(int& child : tree[node])
    {
        if(child == par) continue;

        dfs1(child, node, currDepth + 1);

        siz[node] += siz[child];
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

    dfs1(1, 0, 0);
    dfs2(1, 0);

    for(int i = 1 ; i <= n ; ++i)
    {
        cout << ans[i] << " ";
    }

    cout << "\n";
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
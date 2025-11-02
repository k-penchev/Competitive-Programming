#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;
const int MAXLOG = 20 + 1;

int n, q;
vector<vector<int>> tree(MAXN);
int up[MAXN][MAXLOG];

void dfs(int node, int par)
{
    up[node][0] = par;

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prev = up[node][i - 1];
        up[node][i] = up[prev][i - 1];
    }

    for(const int& child : tree[node])
    {
        if(child == par) continue;
        dfs(child, node);
    }
}

int query(int x, int k)
{
    int node = x;

    for(int i = 0 ; i < MAXLOG ; ++i)
    {
        if(k & (1 << i))
        {
            node = up[node][i];
            if(node == 0) break;
        }
    }

    return (node != 0 ? node : -1);
}

void solve()
{
    cin >> n >> q;

    for(int i = 2 ; i <= n ; ++i)
    {
        int p; cin >> p;
        tree[p].push_back(i);
        tree[i].push_back(p);
    }

    dfs(1, 0);

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int x, k; cin >> x >> k;
        cout << query(x, k) << "\n";
    }
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
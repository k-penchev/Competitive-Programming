#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
int siz[MAXN], dp[MAXN];
int ans = 0;

void dfs_subtree_size(int node, int par)
{
    siz[node] = 1;

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs_subtree_size(to, node);

        siz[node] += siz[to];
    }
}

void dfs_dp(int node, int par)
{
    dp[node] = siz[node];

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs_dp(to, node);

        dp[node] += dp[to];
    }
}

void reroot(int node, int par)
{
    if(dp[node] >= ans)
    {
        ans = dp[node];
    }

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        //reroot
        dp[node] -= dp[to] + siz[to];
        siz[node] -= siz[to];
        siz[to] += siz[node];
        dp[to] += dp[node] + siz[node];

        reroot(to, node);

        //remove reroot
        dp[to] -= dp[node] + siz[node];
        siz[to] -= siz[node];
        siz[node] += siz[to];
        dp[node] += dp[to] + siz[to];
    }
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs_subtree_size(1, 0);
    dfs_dp(1, 0);
    reroot(1, 0);

    cout << ans << "\n";
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
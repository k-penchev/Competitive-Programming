#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int MOD = 1e9 + 7;

int n, k;
vector<vector<int>> tree(MAXN);
int color[MAXN];
int dp[3][MAXN]; 

void dfs(int node, int par)
{
   
    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs(to, node);

        dp[0][node] *= dp[1][to] + dp[2][to];
        dp[1][node] *= dp[0][to] + dp[2][to];
        dp[2][node] *= dp[0][to] + dp[1][to];

        dp[0][node] %= MOD;
        dp[1][node] %= MOD;
        dp[2][node] %= MOD;
    }
}

void solve()
{
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);

    cin >> n >> k;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        dp[0][i] = dp[1][i] = dp[2][i] = 1;
    }

    for(int i = 1 ; i <= k ; ++i)
    {
        int node, c; cin >> node >> c;

        dp[0][node] = dp[1][node] = dp[2][node] = 0;
        dp[c - 1][node] = 1;
    }

    dfs(1, 0);

    cout << (dp[0][1] + dp[1][1] + dp[2][1]) % MOD << "\n";
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
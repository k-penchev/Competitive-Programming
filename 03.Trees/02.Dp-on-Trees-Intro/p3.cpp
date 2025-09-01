#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 50000 + 5;
const int MAXK = 500 + 5;

int n, k;
vector<vector<int>> tree(MAXN);
int dp[MAXN][MAXK];
int ans = 0;

void dfs(int node, int par)
{
    dp[node][0] = 1;
    
    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs(to, node);

        for(int d = 1 ; d <= k ; ++d)
        {
            ans += dp[node][k - d] * dp[to][d - 1];
        }

        for(int d = 1 ; d <= k ; ++d)
        {
            dp[node][d] += dp[to][d - 1];
        }
    }
}

void solve()
{

    cin >> n >> k;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0);

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
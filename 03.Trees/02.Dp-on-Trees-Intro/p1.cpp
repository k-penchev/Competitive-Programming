#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
int dp[2][MAXN];

void dfs(int node, int par)
{
    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs(to, node);

        //get back from child to

        dp[0][node] += max(dp[1][to], dp[0][to]);
    }

    //get back from the node

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dp[1][node] = max(dp[1][node], dp[0][to] + 1 + dp[0][node] - max(dp[0][to], dp[1][to]));
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

    dfs(1, 0);

    cout << max(dp[0][1], dp[1][1]) << "\n";
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
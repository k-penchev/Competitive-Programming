#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 5e5 + 10;
const int NINF = -1e18;

int n;
vector<vector<pair<int, int>>> tree(MAXN);
int cnt[MAXN];
int dp[2][MAXN];

void dfs(int node, int par)
{
    int base = 0;
    vector<int> gains;

    for(const auto& [child, w] : tree[node])
    {
        if(child == par) continue;

        dfs(child, node);

        int best = dp[0][child];

        base += best;

        gains.push_back(w + dp[1][child] - dp[0][child]);
    }

    sort(gains.begin(), gains.end(), [&](int x, int y)
    {
        return x > y;
    });

    //do not take parent
    dp[0][node] = base;
    for(int i = 0 ; i < gains.size() && i < cnt[node] ; ++i)
    {
        if(gains[i] <= 0) break;

        dp[0][node] += gains[i];
    }

    //take parent
    if(cnt[node] == 0)
    {
        dp[1][node] = NINF;
    }
    else
    {
        dp[1][node] = base;
        for(int i = 0 ; i < gains.size() && i < (cnt[node] - 1) ; ++i)
        {
            if(gains[i] <= 0) break;

            dp[1][node] += gains[i];
        }
    }
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> cnt[i];
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b, w; cin >> a >> b >> w;
        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
    }

    dfs(1, 0);

    cout << dp[0][1] << "\n";
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
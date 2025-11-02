#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;

int t, n;
vector<pair<int, int>> range(MAXN);
vector<vector<int>> tree(MAXN);
vector<vector<int>> dp(2, vector<int>(MAXN));

int best(int child, int parent, int type)
{
    if(type == 0)
    {
        int stay = dp[0][child] + abs(range[child].first - range[parent].first);
        int change = dp[1][child] + abs(range[child].second - range[parent].first);
        return max(stay, change);
    }
    else
    {
        int stay = dp[1][child] + abs(range[child].second - range[parent].second);
        int change = dp[0][child] + abs(range[child].first - range[parent].second);
        return max(stay, change);
    }
}

void dfs(int node, int par)
{
    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs(to, node);

        dp[0][node] += best(to, node, 0);
        dp[1][node] += best(to, node, 1);
    }
}

void reset()
{
    std::fill(range.begin(), range.end(), std::pair<int,int>{0,0});

    for (int i = 0; i < MAXN; ++i) tree[i].clear();

    std::fill(dp[0].begin(), dp[0].end(), 0);
    std::fill(dp[1].begin(), dp[1].end(), 0);
}

void solve()
{
    cin >> t;

    while(t--)
    {
        reset();

        cin >> n;

        for(int i = 1 ; i <= n ; ++i)
        {
            cin >> range[i].first >> range[i].second;
        }

        for(int i = 1 ; i <= n - 1 ; ++i)
        {
            int a, b; cin >> a >> b;

            tree[a].push_back(b);
            tree[b].push_back(a);
        }

        dfs(1, 0);

        cout << max(dp[0][1], dp[1][1]) << "\n";
    }
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
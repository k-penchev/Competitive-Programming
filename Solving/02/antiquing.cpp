#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 10;
const int MAXM = 2 * 5e3 + 10;

int n, m, k, c;
int v[MAXN], w[MAXN];
vector<vector<pair<int, int>>> items; // {{v, w} {v, w}},  {},  {}
long long dp[MAXN][MAXM];

void solve()
{
    cin >> n >> m >> k >> c;

    items.resize(n);

    int l, v, w;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> l;
        
        for(int j = 0 ; j < l ; ++j)
        {
            cin >> v >> w;
            items[i].push_back({v, w});
        }
    }

    for(int i = 0 ; i < n ; ++i)
    {
        for(int s = 0 ; s <= m ; ++s)
        {
            if(i != 0)
                dp[i][s] = dp[i - 1][s];
        }

        for(int j = 0 ; j < items[i].size() ; ++j)
        {
            for(int s = 0 ; s <= m ; ++s)
            {
                if (s >= items[i][j].second)
                {
                    dp[i][s] = max(dp[i][s], items[i][j].first + dp[i - 1][s - items[i][j].second]);
                }
            }
        }
        
    }

    long long ans = 0;

    for(int k1 = 0 ; k1 <= m ; ++k1)
    {
        ans = max(ans, dp[n - 1][k1]);
    }

    cout << ans << "\n";
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
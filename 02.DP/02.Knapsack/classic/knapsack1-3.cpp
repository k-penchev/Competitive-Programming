#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

int n, t;
int w[MAXN], v[MAXN];

void solve()
{
    cin >> n >> t;

    vector<int> dp(t + 1, 0);

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> w[i] >> v[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = t ; j >= w[i] ; --j)
        {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }


    cout << dp[t] << "\n";
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
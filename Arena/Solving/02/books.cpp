#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 10;

int n, x;
int h[MAXN], s[MAXN];

void solve()
{
    cin >> n >> x;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> h[i];
    }

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> s[i];
    }

    vector<int> dp(x + 1, 0);

    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = x ; j >= h[i] ; --j)
        {
            dp[j] = max(dp[j], dp[j - h[i]] + s[i]);
        }
    }

    cout << dp[x] << "\n";
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
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e4 + 10;

int n, k;
int a[MAXN];
int dp[MAXN];

void solve()
{
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);

    cin >> n >> k;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> a[i];
    }

    for(int i = 0 ; i < n ; ++i)
    {
        int current_max = 0;

        for(int j = i, cnt = 1 ; j >= 0 && j >= (i - k + 1) ; --j, ++cnt)
        {
            current_max = max(current_max, a[j]);
            dp[i] = max(dp[i], dp[j - 1] + cnt * current_max);
        }
    }

    cout << dp[n - 1] << "\n";
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
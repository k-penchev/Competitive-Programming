#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2e5 + 10;
const int INF = 1e18;

int n, x;
int a[MAXN], dp[MAXN], L[MAXN];
int best = 0;

int lower_binary(int val)
{
    int l = -1, r = n;
    
    while(r > l + 1)
    {
        int m = (l + r) / 2;

        if(dp[m] >= val)
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }

    return r;
}

void reset()
{
    dp[0] = -INF;

    for(int i = 1 ; i <= n ; ++i)
    {
        dp[i] = INF;
    }
}

void solve()
{
    cin >> n >> x;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> a[i];
    }

    reset();

    for(int i = 0 ; i < n ; ++i)
    {
        int len = lower_binary(a[i]);

        dp[len] = a[i];

        L[i] = len;

        best = max(best, L[i]);
    }

    reset();

    for(int i = n - 1 ; i >= 0 ; --i)
    {
        int len = lower_binary(-a[i] + x);

        best = max(best, L[i] + len);

        int pos = lower_binary(-a[i]);

        dp[pos] = -a[i];
    }

    cout << best << "\n";
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
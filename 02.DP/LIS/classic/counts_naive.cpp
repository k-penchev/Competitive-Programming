#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 100000 + 5;
const int NINF = (int)-4e18;
const int PINF = (int) 4e18;

int n;
int a[MAXN];
int dp[MAXN]; 
int cnt[MAXN];

int naive_lis_count()
{
    for(int i = 0 ; i < n ; ++i)
    {
        dp[i] = 1;
        cnt[i] = 1;
    }

    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < i ; ++j)
        {
            if(a[j] < a[i])
            {
                if(dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if(dp[j] + 1 == dp[i])
                {
                    cnt[i] += cnt[j];
                }
            }
        }
    }

    int lis = 0;

    for(int i = 0 ; i < n ; ++i)
    {
        lis = max(lis, dp[i]);
    }

    int ways = 0;

    for(int i = 0 ; i < n ; ++i)
    {
        if(dp[i] == lis)
        {
            ways += cnt[i];
        }
    }
    
    return ways;
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    cout << naive_lis_count() << "\n";
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
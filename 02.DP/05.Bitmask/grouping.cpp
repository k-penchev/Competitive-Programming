#include <bits/stdc++.h>

using namespace std;

typedef long long llong;

const int MAXN = 16;

int N;
llong compatible[MAXN][MAXN];
llong val[(1 << MAXN)]; // precomputed values
llong dp[(1 << MAXN)];

void solve()
{
    cin >> N;

    for(int i = 0 ; i < N ; ++i)
    {
        for(int j = 0 ; j < N ; ++j)
        {
            cin >> compatible[i][j];
        }
    }

    for(int mask = 0 ; mask < (1 << N) ; ++mask)
    {
        for(int first = 0 ; first < N ; ++first)
        {
            if(mask & (1 << first))
            {
                for(int second = first + 1 ; second < N ; ++second)
                {
                    if(mask & (1 << second))
                    {
                        val[mask] += compatible[first][second];
                    }
                }
            }
        }
    }

    dp[0] = 0;

    for(int mask = 0 ; mask < (1 << N) ; ++mask)
    {
        for(int submask = mask ; ; submask = (submask - 1) & mask)
        {
            int subset = mask ^ submask;
            
            int U = subset; // partition 1
            int V = submask; // partition 2

            dp[mask] = max(dp[mask], val[U] + dp[V]);

            if(submask == 0) break; // include empty subset
        }
    }

    cout << dp[(1 << N) - 1] << "\n";
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
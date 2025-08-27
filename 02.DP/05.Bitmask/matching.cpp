#include <bits/stdc++.h>

using namespace std;

const int MAXN = 21;
const int MOD = 1e9 + 7;

int N;
bool compatible[MAXN][MAXN];
int dp[(1 << MAXN)];

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

    dp[0] = 1; // w: {} -> 1

    int fullSetMask = (1 << N) - 1;

    for(int mask = 0 ; mask <= fullSetMask ; ++mask)
    {
        int kth = __builtin_popcount(mask) - 1;

        for(int woman = 0 ; woman < N ; ++woman)
        {
            if(mask & (1 << woman))
            {
                if(compatible[kth][woman])
                {
                    dp[mask] = (dp[mask] + dp[mask ^ (1 << woman)]) % MOD;
                }
            }
        }
    }

    cout << dp[fullSetMask] << "\n";
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
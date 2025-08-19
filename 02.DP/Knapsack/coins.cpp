#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 1e6 + 10;
const int INF = 1e9 + 10;
const int MOD = 1e9 + 7;
 
int n, x;
int coin[MAXN];
int dp[MAXN];
 
void solve()
{
    cin >> n >> x;
 
    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> coin[i];
    }
 
    for(int i = 0 ; i <= x ; ++i)
    {
        dp[i] = INF;
    }
 
    dp[0] = 0;
 
    for(int i = 0 ; i <= x ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            if(i + coin[j] <= x)
            {
                dp[i + coin[j]] = min(dp[i + coin[j]], dp[i] + 1);
            }
        }
    }
 
    cout << ( (dp[x] == INF ) ? -1 : dp[x] ) << "\n";
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
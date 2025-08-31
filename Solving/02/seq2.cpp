#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300;

int n, m;
long long dp[MAXN];

void solve()
{
    //dp[i] -> number of ways for a sequence of length i

    cin >> n >> m;

    dp[0] = 1;

    for(int c = 1 ; c <= m ; ++c)
    {
        for(int s = c ; s <= n ; ++s)
        {
            if(s - c >= 0)
                dp[s] += dp[s - c];
        }
    }
    
    cout << dp[n] << "\n";
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
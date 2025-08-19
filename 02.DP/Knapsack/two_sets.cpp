#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e2 + 10;
const int MOD = 1e9 + 7;
const int MAXS = 63000;

int n;
int dp[MAXS];

void solve()
{
    cin >> n;

    int numSum = n * (n + 1) / 2;

    if(numSum % 2 == 1)
    {
        cout << "0" << "\n";
    }

    int setSum = numSum / 2;

    dp[0] = 1;

    for(int s = 0 ; s < setSum ; ++s)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            if(s + i <= setSum)
            {
                dp[s + i] = (dp[s + i] + dp[i]) % MOD;
            }
        }
    }
    
    cout << dp[setSum] << "\n";
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
#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int MAXK = 5e3 + 10;

int q, k;
vector<int> bag;
int dp[MAXK];

void solve()
{
    cin >> q >> k;

    dp[0] = 1;

    char type;
    int x;

    for(int qq = 0 ; qq < q ; ++qq)
    {
        cin >> type >> x;

        if(type == '+')
        {
            for(int i = k ; i >= x ; --i)
            {
                dp[i] = (dp[i] + dp[i - x]) % MOD;
            }
        }
        else
        {
            for(int i = x ; i <= k ; ++i)
            {
                dp[i] = (dp[i] - dp[i - x]) % MOD;
            }
        }

        cout << dp[k] << "\n";
    }
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
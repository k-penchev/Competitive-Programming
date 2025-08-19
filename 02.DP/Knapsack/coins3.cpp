#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;

int n, x;
vector<int> coin;
int dp[MAXN];

void solve()
{
    cin >> n >> x;

    for(int i = 0 ; i < n ; ++i)
    {
        int c; cin >> c;
        coin.push_back(c);
    }

    dp[0] = 1;

    for(int c : coin)
    {
        for(int s = 0 ; s < x ; ++s)
        {
            if(s + c <= x)
            {
                dp[s + c] = (dp[s] + dp[s + c]) % MOD;
            }
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
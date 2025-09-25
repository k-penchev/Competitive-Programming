#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int n, x;
vector<int> coins;

void solve()
{
    cin >> n >> x;

    for(int i = 0 ; i < n ; ++i)
    {
        int coin; cin >> coin;
        coins.push_back(coin);
    }

    vector<int> dp(x + 1, INF);

    dp[0] = 0;

    for(int s = 0 ; s < x ; ++s)
    {
        for(int c : coins)
        {
            if(s + c <= x)
            {
                dp[s + c] = min(dp[s + c], dp[s] + 1);
            }
        }
    }

    cout << ( dp[x] == INF ? -1 : dp[x] ) << "\n";
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
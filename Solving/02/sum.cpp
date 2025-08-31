#include <bits/stdc++.h>

using namespace std;

const int MAXS = 2e4 + 10;
const int INF = 1e9;

int s, n;
vector<int> cards;
long long dp[MAXS];

void solve()
{
    cin >> s >> n;

    for(int i = 0 ; i < n ; ++i)
    {
        int x; cin >> x;
        cards.push_back(x);
    }

    for(int i = 1 ; i <= s ; ++i)
    {
        dp[i] = INF;
    }

    dp[0] = 0;

    for(int sum = 0 ; sum < s ; ++sum)
    {
        for(int card : cards)
        {
            if(sum + card <= s && dp[sum] != INF)
            {
                dp[sum + card] = min(dp[sum + card], dp[sum] + 1);
            }
        }
    }

    cout << dp[s] << "\n";
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
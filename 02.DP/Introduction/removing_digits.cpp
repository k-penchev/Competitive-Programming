#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
const int INF = 1e9 + 10;
const int MOD = 1e9 + 7;

int n;
int dp[MAXN];

void solve()
{
    cin >> n;

    for(int i = 0 ; i <= n ; ++i)
    {
        dp[i] = INF;
    }

    dp[n] = 0;  //dp[i]

    for(int i = n ; i >= 1 ; --i)
    {
        int current_number = i;
        
        while(current_number)
        {
            int last_digit = current_number % 10;
            dp[i - last_digit] = min(dp[i - last_digit], dp[i] + 1);
            current_number /= 10;
        }
    }
 
    cout << dp[0] << "\n";
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
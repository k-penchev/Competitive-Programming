#include <bits/stdc++.h>

using namespace std;

string st1, st2;

void solve()
{
    cin >> st1 >> st2;

    int n = st1.size();
    int m = st2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= m ; ++j)
        {
            if(st1[i - 1] == st2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    vector<char> lcs;

    int lPtr = n, rPtr = m;

    while(lPtr > 0 && rPtr > 0)
    {
        if(st1[lPtr - 1] == st2[rPtr - 1])
        {
            lcs.push_back(st1[lPtr - 1]);
            --lPtr;
            --rPtr;
        }
        else if(dp[lPtr - 1][rPtr] > dp[lPtr][rPtr - 1])
        {
            --lPtr;
        }
        else
        {
            --rPtr;
        }
    }

    reverse(lcs.begin(), lcs.end());

    for(char c : lcs)
    {
        cout << c;
    }

    cout << "\n";

    //cout << dp[n][m] << "\n";
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
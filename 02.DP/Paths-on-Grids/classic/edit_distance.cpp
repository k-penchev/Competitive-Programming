#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

string x, y;

void solve()
{
    cin >> x >> y;

    int A = x.size();
    int B = y.size();

    vector<vector<int>> dp(A + 1, vector<int>(B + 1, INF));

    dp[0][0] = 0;

    for(int i = 0 ; i <= A ; ++i)
    {
        for(int j = 0 ; j <= B ; ++j)
        {
            if(i != 0)
            {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            }

            if(j != 0)
            {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }

            if(i != 0 && j != 0)
            {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (x[i - 1] != y[j - 1]));
            }
        }
    }

    cout << dp[A][B] << "\n";
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
#include <bits/stdc++.h>

using namespace std;

string st1, st2;

void solve()
{
    cin >> st1 >> st2;

    if(st2.size() > st2.size()) swap(st1, st2);

    int n = st1.size();
    int m = st2.size();

    vector<int> dp(m + 1, 0);

    for(int i = 1 ; i <= n ; ++i)
    {
        int prev = dp[0];

        for(int j = 1 ; j <= m ; ++j)
        {

            int temp = dp[j];

            if(st1[i - 1] == st2[j - 1])
            {
                dp[j] = 1 + prev;
            }
            else
            {
                dp[j] = max(dp[j - 1], dp[j]);
            }

            prev = temp;
        }

    }

    cout << dp[m] << "\n";
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
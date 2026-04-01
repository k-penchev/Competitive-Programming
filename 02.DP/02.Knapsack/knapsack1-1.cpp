#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

int n, t;
int w[MAXN], v[MAXN];

void solve()
{
    cin >> n >> t;

    vector<vector<int>> dp(n + 1, vector<int>(t + 1, 0));

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> w[i] >> v[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 0 ; j <= t ; ++j)
        {
            dp[i][j] = dp[i - 1][j];

            if (j >= w[i])
            {
                dp[i][j] = max(dp[i][j], v[i] + dp[i - 1][j - w[i]]);
            }
        }
    }


    vector<int> items;
    
    int l = n, r = t;
    
    while (l > 0)
    {
        // if taking l was feasible and yields current dp value, we took it
        if (r >= w[l] && dp[l][r] == dp[l-1][r - w[l]] + v[l])
        {
            items.push_back(l);
            r -= w[l];
        }
        --l;
        if (r == 0) break; 
    }
    
    reverse(items.begin(), items.end());


    for(int it : items)
    {
        cout << it << " ";
    }

    cout << "\n";

    /*
    
    for(int i = 0 ; i <= n ; ++i)
    {
        cout << "i=" << i << "  ";

        for(int j = 0 ; j <= t ; ++j)
        {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";
    
    */

    cout << dp[n][t] << "\n";
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
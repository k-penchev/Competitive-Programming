#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, t;
int w[MAXN], v[MAXN], k[MAXN];

void solve()
{
    cin >> n >> t;
    
    for(int i = 0 ; i < n ; ++i)
    {
        cin >> w[i] >> v[i] >> k[i];
    }

    vector<int> dp(t + 1, 0);

    for(int i = 0 ; i < n ; ++i)
    {
        int w_i = w[i], v_i = v[i], k_i = k[i];

        while(k_i--)
        {
            for(int j = t ; j >= w_i ; --j)
            {
                dp[j] = max(dp[j], dp[j - w_i] + v_i);
            }
        }
    }

    cout << dp[t] << "\n";
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
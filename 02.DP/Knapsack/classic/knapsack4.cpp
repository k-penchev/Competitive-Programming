#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int INF = 1e9;

int n, t;

struct Item
{
    int w;
    int v;
};

vector<Item> zeroOne, unbounded;

void solve()
{
    cin >> n >> t;

    int w_i, v_i, k_i;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> w_i >> v_i >> k_i;

        if(k_i == INF)
        {
            unbounded.push_back({w_i, v_i});
        }
        else if(k_i == 1)
        {
            zeroOne.push_back({w_i, v_i});
        }
        else
        {
            int p = 1;

            while(p <= k_i)
            {
                k_i -= p;

                zeroOne.push_back({w_i * p, v_i * p});

                p *= 2;
            }

            if(k_i)
            {
                zeroOne.push_back({w_i * k_i, v_i * k_i});
            }
        }
    }

    vector<int> dp(t + 1, 0);


    for(auto it : zeroOne)
    {
        for(int j = t ; j >= it.w ; --j)
        {
            dp[j] = max(dp[j], dp[j - it.w] + it.v);
        }
    }

    for(auto it : unbounded)
    {
        for(int j = it.w ; j <= t ; ++j)
        {
            dp[j] = max(dp[j], dp[j - it.w] + it.v);
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
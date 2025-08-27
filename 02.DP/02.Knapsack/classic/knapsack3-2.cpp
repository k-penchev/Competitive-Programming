#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, t;
vector<pair<int, int>> items;

void solve()
{
    cin >> n >> t;
    
    int w, v, cnt;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> w >> v >> cnt;

        int p = 1;

        while(p <= cnt)
        {
            cnt -= p;

            items.push_back({w * p, v * p});

            p *= 2;
        }

        if(cnt)
        {
            items.push_back({w * cnt, v * cnt});
        }

    }

    vector<int> dp(t + 1, 0);

    for(auto item : items)
    {
        int w_i = item.first, v_i = item.second;

        for(int j = t ; j >= w_i ; --j)
        {
            dp[j] = max(dp[j], dp[j - w_i] + v_i);
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
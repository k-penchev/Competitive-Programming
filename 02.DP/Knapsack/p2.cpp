#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e2 + 10;

int w[MAXN], v[MAXN], k[MAXN];

int N, W;
vector<pair<int, int>> items;

void solve()
{
    cin >> N >> W;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> w[i];
    }

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> v[i];
    }

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> k[i];
    }


    int w_i, v_i, k_i;

    for(int i = 0 ; i < N ; ++i)
    {
        w_i = w[i], v_i = v[i], k_i = k[i];

        int p = 1;

        while(p <= k_i)
        {
            k_i -= p;

            items.push_back({w_i * p, v_i * p});

            p *= 2;
        }

        if(k_i)
        {
            items.push_back({w_i * k_i, v_i * k_i});
        }
    }

    vector<int> dp(W + 1, 0);

    for(auto& it : items)
    {
        for(int j = W ; j >= it.first ; --j)
        {
            dp[j] = max(dp[j], dp[j - it.first] + it.second);
        }
    }

    cout << dp[W] << "\n";
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
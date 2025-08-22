#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 5e3 + 10;
const int MAXM = 5e3 + 10;
const int INF = 1e9;

int N, M, W = 0;
vector<pair<int, int>> items;
int c[MAXM], f[MAXM];

void solve()
{
    cin >> N >> M;

    int x, y, z;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> z >> x >> y;

        int p = 1; 

        while(p <= z)
        {
            z -= p;

            items.push_back({x * p, y * p});

            p *= 2;
        }

        if(z)
        {
            items.push_back({x * z, y * z});
        }
    }

    for(int i = 0 ; i < M ; ++i)
    {
        cin >> c[i] >> f[i];
        W = max(W, c[i]);
    }

    vector<int> dp(W + 1, 0);

    for(auto& it : items)
    {
        for(int j = W ; j >= it.first ; --j)
        {
            dp[j] = max(dp[j], dp[j - it.first] + it.second);
        }
    }


    int best_profit = -INF;

    for(int i = 0 ; i < M ; ++i)
    {
        int current_profit = dp[c[i]] - f[i];
        best_profit = max(best_profit, current_profit);
    }

    cout << best_profit << "\n";
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
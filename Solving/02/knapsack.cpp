#include <bits/stdc++.h>

#define int long long

using namespace std;

int S, N;
vector<pair<int, int>> items;

void solve()
{
    cin >> S >> N;

    int price, award, cnt;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> award >> price >> cnt;

        int p = 1;

        while(p <= cnt)
        {
            cnt -= p;

            items.push_back({price * p, award * p});

            p *= 2;
        }

        if(cnt)
        {
            items.push_back({price * cnt, award * cnt});
        }
    }

    int dp[S + 1] = {0};

    for(auto& it : items)
    {
        for(int j = S ; j >= it.first ; --j)
        {
            dp[j] = max(dp[j], dp[j - it.first] + it.second);
        }
    }

    cout << dp[S] << "\n";
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
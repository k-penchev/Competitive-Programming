#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e2 + 10;

int N, W;
int w[MAXN], v[MAXN];

void solve()
{
    cin >> N >> W;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> w[i] >> v[i];
    }

    vector<int> dp(W + 1, 0);

    for(int i = 0 ; i < N ; ++i)
    {
        for(int j = W ; j >= w[i] ; --j)
        {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
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
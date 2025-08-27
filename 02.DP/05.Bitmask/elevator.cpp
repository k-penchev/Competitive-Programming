#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;
const int INF = 1e9 + 10;

int N, X;
int w[MAXN];
pair<int, int> dp[(1 << MAXN)];

void solve()
{
    cin >> N >> X;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> w[i];
    }

    for(int i = 0 ; i < (1 << N) ; ++i)
    {
        dp[i] = {INF, 0};
    }

    dp[0] = {1, 0};

    for(int mask = 0 ; mask < (1 << N) ; ++mask)
    {
        for(int i = 0 ; i < N ; ++i)
        {
            if((mask & (1 << i)))
            {
                auto option = dp[mask ^ (1 << i)];

                if(option.second + w[i] <= X)
                {
                    option.second += w[i];
                }
                else
                {
                    option.first++;
                    option.second = w[i];
                }

                dp[mask] = min(dp[mask], option);
            }
        }
    }

    cout << dp[(1 << N) - 1].first << "\n";
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
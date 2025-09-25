#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250 + 5;

float N, W;
int w[MAXN], t[MAXN];

struct Cell
{
    double total_w;
    double total_t;
    double ratio;
};

Cell f(const Cell& c1, const Cell& c2)
{
    if(c1.ratio > c2.ratio)
    {
        return c1;
    }
    else
    {
        return c2;
    }
}

void solve()
{
    cin >> N >> W;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> w[i] >> t[i];
    }

    vector<vector<Cell>> dp(N + 1, vector<Cell>(W + 1));

    dp[0][0] = {0, 0, 0};

    for(int i = 1 ; i <= N ; ++i)
    {
        for(int j = 0 ; j <= W ; ++j)
        {

            dp[i][j] = f(dp[i][j], dp[i - 1][j]);

            if(j >= w[i])
            {
                Cell temp = dp[i - 1][j - w[i]];

                temp.total_w += w[i];
                temp.total_t += t[i];
                temp.ratio = temp.total_t / temp.total_w;

                dp[i][j] = f(dp[i][j], temp);
            }

        }
    }

    cout << dp[N][W].ratio << "\n";
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
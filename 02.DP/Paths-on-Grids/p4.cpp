#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 10;

int N;
int l[MAXN], r[MAXN];
int dp[MAXN][MAXN];

bool check(int x, int y)
{
    return (abs(x - y) <= 4);
}

void solve()
{
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);

    cin >> N;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> l[i];
    }

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> r[i];
    }

    for(int col = 0 ; col < N ; ++col)
    {
        dp[0][col] = check(l[0], r[col]);
    }

    for(int row = 0 ; row < N ; ++row)
    {
        dp[row][0] = check(l[row], r[0]);
    }

    for(int i = 1 ; i < N ; ++i)
    {
        for(int j = 1 ; j < N ; ++j)
        {
            int diagonal = dp[i - 1][j - 1] + check(l[i], r[j]);

            dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], diagonal});
        }
    }


    cout << dp[N - 1][N - 1] << "\n";
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
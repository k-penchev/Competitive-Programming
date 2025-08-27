#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXK = 20 + 5;

int n, k;
int moves[MAXN]; // 0 -> Hoof, 1 -> Paper, 2 -> Scissors
int dp[MAXN][MAXK][3];

bool play(int x, int y)
{
    return (x == (y + 1) % 3);
}

void solve()
{
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    cin >> n >> k;
    
    char m;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> m;

        if(m == 'H')
        {
            moves[i] = 0;
        }
        else if(m == 'P')
        {
            moves[i] = 1;
        }
        else
        {
            moves[i] = 2;
        }
    }

    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j <= k ; ++j)
        {
            for(int m = 0 ; m < 3 ; ++m)
            {
                bool isWin = play(m, moves[i]); // 1 -> the cow won , 0 -> the farmer won

                if(isWin)
                {
                    ++dp[i][j][m];
                }

                dp[i + 1][j + 1][0] = max(dp[i + 1][j + 1][0], dp[i][j][m]);
                dp[i + 1][j + 1][1] = max(dp[i + 1][j + 1][1], dp[i][j][m]);
                dp[i + 1][j + 1][2] = max(dp[i + 1][j + 1][2], dp[i][j][m]);

                dp[i + 1][j][m] = max(dp[i + 1][j][m], dp[i][j][m]);
            }
        }
    }

    int answer = 0;

    for(int m = 0 ; m < 3 ; ++m)
    {
        answer = max(answer, dp[n][k][m]);
    }

    cout << answer << "\n";
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
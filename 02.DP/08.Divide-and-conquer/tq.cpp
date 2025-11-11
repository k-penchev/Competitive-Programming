#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXQ = 2e5 + 10;
const int INF = 1e9 + 10;

int n, m, q;
std::vector<std::vector<int>> table;
std::vector<std::vector<int>> dp;

int calc(int x1, int y1, int x2, int y2)
{
    dp[x1][y1] = table[x1][y1];
    for(int i = x1 ; i <= x2 ; ++i)
    {
        for(int j = y1 ; j <= y2 ; ++j)
        {
            dp[i][j] = table[i][j];

            int pull = INF;
    
            if(i - 1 >= x1)
            {
                pull = std::min(pull, dp[i - 1][j]);
            }

            if(j - 1 >= y1)
            {
                pull = std::min(pull, dp[i][j - 1]);
            }

            dp[i][j] += (pull != INF ? pull : 0);
        }
    }

    return dp[x2][y2];
}

void solve()
{
    std::cin >> n >> m >> q;

    table.resize(n + 1);
    dp.resize(n + 1);
    for(int i = 1 ; i <= n ; ++i)
    {
        table[i].resize(m + 1);
        dp[i].resize(m + 1);
        for(int j = 1 ; j <= m ; ++j)
        {
            std::cin >> table[i][j];
        }
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int x1, x2, y1, y2;
        std::cin >> x1 >> x2 >> y1 >> y2;
        std::cout << calc(x1, x2, y1, y2) << "\n";
    }
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
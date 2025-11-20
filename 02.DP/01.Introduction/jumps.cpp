#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 300 + 5;
const int MAXM = 300 + 5;
const int MAXK = 300 + 5;
const int MOD = 1e9 + 7;

int n, m, a, b, k;

bool memo[MAXN][MAXM][MAXK];
int dp[MAXN][MAXM][MAXK];

int f(int x, int y, int rem)
{
    if(rem == 0)
    {
        if(x == 0 && y == 0) return 1;
        return 0;
    }

    if(memo[x][y][rem]) return dp[x][y][rem];

    memo[x][y][rem] = 1;

    for(int i = 0 ; i <= a ; ++i)
    {
        if(x - i < 0) break;

        for(int j = 0 ; j <= b ; ++j)
        {
            if(y - j < 0) break;
    
            dp[x][y][rem] = (dp[x][y][rem] + f(x - i, y - j, rem - 1)) % MOD;
        }
    }

    return dp[x][y][rem];
}

void solve()
{
    std::cin >> n >> m >> a >> b >> k;
    std::cout << f(n, m, k) << "\n";
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
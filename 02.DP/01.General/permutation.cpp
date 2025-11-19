#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 3000 + 5;
const int MOD = 1e9 + 7;

int n;
char a[MAXN];
long long ans;

bool memo[MAXN][MAXN];
int dp[MAXN][MAXN];

int f(int pos, int rank)
{
    if(pos == 1)
    {
        return (rank == 1);
    }

    if(memo[pos][rank]) return dp[pos][rank];

    memo[pos][rank] = 1;

    if(a[pos - 1] == '<')
    {
        for(int i = 1 ; i < rank ; ++i)
        {
            dp[pos][rank] = (dp[pos][rank] + f(pos - 1, i)) % MOD;
        }
    }
    else
    {
        for(int i = rank ; i <= pos - 1 ; ++i)
        {
            dp[pos][rank] = (dp[pos][rank] + f(pos - 1, i)) % MOD;
        }
    }

    return dp[pos][rank];
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        std::cin >> a[i];
    }

    for(int rank = 1 ; rank <= n ; ++rank)
    {
        ans = (ans + f(n, rank)) % MOD;
    }

    std::cout << ans << "\n";
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

#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 1000000 + 10;
const int MOD = 998244353;

int n, m, k;
llong dp[2 * MAXN];
llong total;
llong sum;

void solve()
{
    std::cin >> n >> m >> k;

    sum = dp[n + 1] = 1;
    for(int i = n ; i >= 1 ; --i)
    {
        dp[i] = ((m - 1) + (i == 1)) * sum;
        dp[i] %= MOD;

        sum += dp[i];
        sum -= dp[i + k - 1];
        sum += MOD;
        sum %= MOD;
    }

    total = 1;
    for(int i = 1 ; i <= n ; ++i)
    {
        total *= m;
        total %= MOD;
    }

    std::cout << (total - dp[1] + MOD) % MOD << "\n";
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
    return 0;
}
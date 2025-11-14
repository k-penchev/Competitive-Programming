#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 1e5 + 10;
const int INF = 1e18;

int n;
int a[MAXN];
int dp[MAXN];
bool memo[MAXN];

int f(int idx)
{
    if(idx == 1) return 0;
    if(memo[idx]) return dp[idx];
    
    memo[idx] = 1;

    if(idx - 1 >= 1)
    {
        dp[idx] = std::min(dp[idx], f(idx - 1) + std::abs(a[idx] - a[idx - 1]));
    }

    if(idx - 2 >= 1)
    {
        dp[idx] = std::min(dp[idx], f(idx - 2) + std::abs(a[idx] - a[idx - 2]));
    }

    return dp[idx];
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    std::fill(dp + 1, dp + n + 1, INF);
    std::cout << f(n) << "\n";
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
}
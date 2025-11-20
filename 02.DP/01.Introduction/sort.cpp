#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 1000 + 10;
const int MAXV = 10000 + 10;
const int INF = 1e18 + 10;

int n;
int a[MAXN];
int ans, min, max;

int dp[MAXN][MAXV];

void solve()
{
    std::cin >> n;

    min = +INF, max = -INF;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        min = std::min(min, a[i]);
        max = std::max(max, a[i]);
    }

    for(int val = min ; val <= max ; ++val)
    {
        dp[1][val] = std::abs(a[1] - val);
    }

    for(int pos = 2 ; pos <= n ; ++pos)
    {
        int best = INF;
        for(int val = min ; val <= max ; ++val)
        {
            best = std::min(best, dp[pos - 1][val]);
            dp[pos][val] = best + std::abs(a[pos] - val);
        }
    }

    ans = INF;
    for(int val = min ; val <= max ; ++val)
    {
        ans = std::min(ans, dp[n][val]);
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
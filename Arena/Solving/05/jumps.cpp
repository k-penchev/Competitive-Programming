#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n;
int a[MAXN];
long long dp[MAXN];

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = i + 2 ; j <= n ; ++j)
        {
            dp[j] = std::max(dp[j], dp[i] + a[j]);
        }
    }

    std::cout << dp[n] << "\n";
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
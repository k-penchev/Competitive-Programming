#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 1e5 + 10;

int n;
int a[MAXN][4];
bool memo[MAXN][4];
int dp[MAXN][4];

int f(int day, int last)
{
    if(day == n + 1) return 0;
    if(memo[day][last]) return dp[day][last];

    memo[day][last] = 1;
    for(int i = 0 ; i <= 2 ; ++i)
    {
        if(last == i) continue;
        dp[day][last] = std::max(dp[day][last], f(day + 1, i) + a[day][i]);
    }

    return dp[day][last];
}


void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i][0] >> a[i][1] >> a[i][2];
    }

    std::cout << f(1, 3) << "\n";
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
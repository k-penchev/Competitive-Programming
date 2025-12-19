//count permutations with inversions between L and R
#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 500 + 10;
const int MOD = 1e9 + 7;

int n, l, r;
int dp[MAXN][MAXN * MAXN / 2]; // dp[i][j] -> consider only the first "i" elements with exactly "j" inversions
bool bl[MAXN][MAXN * MAXN / 2];

int f(int i, int j)
{
    if(i == 0 && j == 0) return 1;
    
    if(bl[i][j]) return dp[i][j];
    bl[i][j] = true;

    for(int k = 0 ; k <= std::min(i - 1, j) ; ++k)
    {
        dp[i][j] = (dp[i][j] + f(i - 1, j - k)) % MOD;
    }

    return dp[i][j];
}

void solve()
{
    std::cin >> n >> l >> r;

    int sum = 0;

    for(int i = l ; i <= r ; ++i)
    {
        sum = (sum + f(n, i)) % MOD;
    }

    std::cout << sum << "\n";
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
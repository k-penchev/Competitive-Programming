#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 80 + 5;
const int MAXT = 250 + 5;
const int MAXW = 1e7 + 5;

int n, k;

struct Person
{
    int w;
    int t;
};

Person p[MAXN];
int dp[MAXN][MAXN][MAXN * MAXT];
int best;

void solve()
{
    std::cin >> n >> k;

    for(int i = 0 ; i < n ; ++i)
    {
        std::cin >> p[i].w >> p[i].t;
    }

    for(int b = 0 ; b <= k ; ++b) dp[0][b][0] = 0;

    for(int a = 0 ; a < n ; ++a)
    {
        for(int b = k ; b >= 0 ; --b)
        {
            for(int s = 0 ; s < MAXN * MAXT ; ++s)
            {
                int current_state = dp[a][b][s];

                dp[a + 1][b][s] = std::min(dp[a + 1][b][s], current_state);

                int new_s = s + p[a].t;

                if(new_s < MAXN * MAXT && b - 1 >= 0)
                {
                    dp[a + 1][b - 1][new_s] = std::max(current_state, new_s);
                }
            }
        }
    }

    std::cout << dp[n][k][] << "\n";
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
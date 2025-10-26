#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int MAXLOG = 20 + 1;

int n, k;
int a[MAXN];
int lift[MAXN][MAXLOG];
int sum[MAXN];
int bestScore = -1;
std::vector<int> bestID;

void solve()
{
    std::cin >> n >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> lift[i][0];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j < MAXLOG ; ++j)
        {
            int prev = lift[i][j - 1];
            lift[i][j] = lift[prev][j - 1];
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        int current = i;

        for(int j = MAXLOG - 1 ; j >= 0 ; --j)
        {
            if(k & (1 << j))
            {
                current = lift[current][j];
            }
        }

        sum[current] += a[i];
    }

    bestScore = *std::max_element(sum + 1, sum + n + 1);

    std::cout << bestScore << "\n";
    for(int i = 1 ; i <= n ; ++i)
    {
        if(sum[i] == bestScore)
        {
            std::cout << i << " ";
        }
    }
    
    std::cout << "\n";
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
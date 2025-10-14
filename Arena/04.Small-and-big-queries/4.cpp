#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e6 + 10;

int n, q;
int a[MAXN];
bool included[MAXN];

int query(int x, int y)
{
    int swaps = 1e9, curr_swaps = 0;
    std::fill(included + 1, included + n + 1, 0);

    for(int i = 1 ; i <= n ; ++i)
    {
        if(a[i] == x || a[i] == y)
        {
            included[i] = 1;
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(included[i])
        {
            int l = 0, r = 0, curr_swaps = 0;
            for(int j = i - 1 ; j >= 1 ; --j)
            {
                if(included[j])
                {
                    curr_swaps += (i - j - 1) - l;
                    l += 1;
                }
            }

            for(int j = i + 1 ; j <= n ; ++j)
            {
                if(included[j])
                {
                    curr_swaps += (j - i - 1) - r;
                    r += 1;
                }
            }

            swaps = std::min(swaps, curr_swaps);
        }
    }

    return swaps;
}

void solve()
{
    std::cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)  
    {
        std::cin >> a[i];
    }
    
    for(int i = 1 ; i <= q ; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        std::cout << query(x, y) << "\n";
    }
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
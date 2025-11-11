#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 500 + 10;

int n, m, k;

struct Point
{
    int x;
    int y;
};

Point sheep[MAXN];
Point house[MAXN];

void solve()
{
    std::cin >> n >> m >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> sheep[i].x >> sheep[i].y;
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        std::cin >> house[i].x >> house[i].y;
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
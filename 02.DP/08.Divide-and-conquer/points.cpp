#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 5 * 1e5 + 10;

int n, k;

struct MST
{

};

struct Point
{
    int x, y;
};

long long ans = 0;
Point point[MAXN];
MST mstPlus;
MST mstMinus;

void solve()
{
    std::cin >> n >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> point[i].x >> point[i].y;
    }

    std::sort(point + 1, point + n + 1, [&](const Point &a, const Point &b)
    {
        return a.x < b.x;
    });

    for(int i = 1 ; i <= n ; ++i)
    {
        //ans
    }

    std::cout << ans << "\n";
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
}
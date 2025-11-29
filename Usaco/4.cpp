#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#define int long long

const int MAXP = 2 * 1e5 + 10;
const int INF = 1e18;

int n, p;

struct Point
{
    int x;
    int y;

    inline friend bool operator < (const Point &a, const Point &b)
    {
        return (a.x <= b.x && a.y <= b.y);
    }
};

int dp[MAXP];
std::vector<Point> point;
std::map<std::pair<int, int>, std::pair<int, int>> map;

int distance(const Point &a, const Point &b)
{
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int cost(const Point &a, const Point &b)
{
    auto [x_prim, y_prim] = map[{a.x, a.y}];
    
    if(b.x == x_prim && b.y == y_prim)
    {
        return 0;
    }

    return distance(a, b);
}

void solve()
{
    std::freopen("boards.in", "r", stdin);
    std::freopen("boards.out", "w", stdout);

    std::cin >> n >> p;

    for(int i = 1 ; i <= p ; ++i)
    {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        
        point.push_back({x1, y1});
        point.push_back({x2, y2});
        map[{x1, y1}] = {x2, y2};
    }

    point.push_back({0, 0});
    point.push_back({n, n});

    p = 2 * p + 2;

    dp[0] = 0;
    std::fill(dp + 1, dp + p, INF);

    std::sort(point.begin(), point.end());
    for(int i = 0 ; i < point.size() ; ++i)
    {
        for(int j = i + 1 ; j < point.size() ; ++j)
        {
            if(!(point[i] < point[j])) continue;

            dp[j] = std::min(dp[j], dp[i] + cost(point[i], point[j]));
        }   
    }

    std::cout << dp[p - 1] << "\n";
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
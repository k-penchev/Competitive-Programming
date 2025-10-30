#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>

typedef long long llong;
const int MAXN = 1e6 + 10;
const long double MAX_X = 1e19 + 10;
const llong INF = 1e19 + 10;

int n;
 
struct Line
{
    long double a, b;
    long double from;
 
    long double at(long double x)
    {
        return a * x + b;
    }
};
 
long double intersect(Line x, Line y)
{
    return ((y.b - x.b) / (x.a - y.a));
}
 
struct CHT_MAX
{
    std::vector<Line> hull;
 
    void push(Line x)
    {
        x.from = +MAX_X;
 
        while(hull.size() && hull.back().at(hull.back().from) < x.at(hull.back().from))
        {
            hull.pop_back();
        }
 
        if(hull.empty()) hull.push_back({x.a, x.b, +(long double)MAX_X});
        else if(x.at(-MAX_X) > hull.back().at(-MAX_X)) hull.push_back({x.a, x.b, intersect(hull.back(), x)});
 
    }
 
    long double query(long double x)
    {
        if(hull.empty()) return 0;
 
        int l = 0, r = hull.size();
 
        while(l + 1 < r)
        {
            int mid = (l + r) / 2;
 
            if(hull[mid].from >= x) l = mid;
            else r = mid;
        }
 
        assert(l < hull.size());
        return hull[l].at(x);
    }
};
 
CHT_MAX hull;

struct Range
{
    int x, y;
    llong a;
};
 
Range rectangles[MAXN];
 
void solve()
{
    std::cin >> n;
 
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> rectangles[i].x >> rectangles[i].y >> rectangles[i].a;
    }
 
    std::sort(rectangles + 1, rectangles + n + 1, [&](const Range& r1, const Range& r2)
    {
        return r1.x < r2.x;
    });
 
    hull.push({0, 0, +MAX_X});
    llong result = -INF, current;
    for(int i = 1 ; i <= n ; ++i)
    {
        current = 1LL * rectangles[i].x * rectangles[i].y - rectangles[i].a + std::llround(hull.query((long double)rectangles[i].y));
        hull.push({-(long double)rectangles[i].x, (long double)current, +(long double)MAX_X});
 
        result = std::max(result, current);
    }
 
    std::cout << result << "\n";
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
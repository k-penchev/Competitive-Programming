#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 1e6 + 10;
const int MAX_X = 1e9 + 10;

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
        x.from = -MAX_X;

        while(hull.size() && hull.back().at(hull.back().from) < x.at(hull.back().from))
        {
            hull.pop_back();
        }

        if(hull.empty()) hull.push_back({x.a, x.b, -(long double)MAX_X});
        else if() hull.push_back({x.a, x.b, intersect(hull.back(), x)});

    }

    long double query(long double x)
    {

    }
};

CHT_MAX hull;

int dp[MAXN];

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        int x, y, a;
        std::cin >> x >> y >> a;

        //dp[i] = x * y - a + max(-xj * yi + dp[j])
        //dp[i] = x * y - a + hull.query(y)
        //hull.push({})
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
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 1e5 + 10;
const int MAX_X = 1e6 + 10;

int n;

struct Line
{
    long double a, b;
    long double from;

    long double at(long double x)
    {
        return a * x + b;
    };
};

long double intersect(Line x, Line y)
{
    return (y.b - x.b) / (x.a - y.a);
}

struct CHT_MIN
{
    std::vector<Line> hull;

    void build(std::vector<std::pair<long double, long double>>& v)
    {
        std::sort(v.begin(), v.end(), [&](const auto x, const auto y)
        {
            x.first > y.first;
        });

        for(const auto& x : v)
        {
            push({x.first, x.second, -(long double)MAX_X});
        }
    }

    void push(Line x)
    {
        x.from = -MAX_X;

        while(hull.size() && hull.back().at(hull.back().from) > x.at(hull.back().from))
        {
            hull.pop_back();
        }

        if(hull.empty()) hull.push_back(x);
        else if(x.at(MAX_X) < hull.back().at(MAX_X)) hull.push_back({x.a, x.b, intersect(hull.back(), x)});
    }

    long double query(long double x)
    {
        int l = 0, r = hull.size();
        
        while(l + 1 < r)
        {
            int m = (l + r) / 2;

            if(hull[m].from <= x) l = m;
            else r = m;
        }

        assert(l < hull.size());
        long double ans = hull[l].at(x);

        return ans;
    }
};

CHT_MIN hull;

void solve()
{
    
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
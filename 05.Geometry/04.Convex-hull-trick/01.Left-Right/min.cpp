#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
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
    return (y.b - x.b) / (x.a - y.a);
}

struct CHT_MIN
{   
    std::vector<Line> hull;

    //decreasing lines
    void push(Line x)
    {
        while(hull.size() && hull.back().at(hull.back().from) > x.at(hull.back().from))
        {
            hull.pop_back();
        }

        if(hull.empty()) hull.push_back(x);
        else if(x.at(+MAX_X) < hull.back().at(+MAX_X)) hull.push_back({x.a, x.b, intersect(hull.back(), x)});
    }

    long double binary(long double x)
    {
        int l = 0, r = hull.size();

        while(l + 1 < r)
        {
            int mid = (l + r) / 2;

            if(hull[mid].from <= x) l = mid;
            else r = mid;
        }

        return hull[l].at(x);
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
}
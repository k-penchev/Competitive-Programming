#include <algorithm>
#include <iostream>
#include <numeric>
#include <cassert>
#include <vector>
#include <chrono>
#include <random>

typedef long long llong;
const int MAX_X = 1e6 + 10;
const int MAXN = 1e5 + 10;
const int MAXLOG = 20;
const int INF  = 1e9;

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
    std::vector <Line> hull;
    void build(std::vector <std::pair <long double, long double>> &v)
    {
        std::sort(v.begin(), v.end(), [&](auto x, auto y)
        {
            return x.first > y.first;
        });
        
        for (const auto &x : v)
        {
            push({x.first, x.second, -MAX_X});
        }
    }
    
    void push(Line x)
    {
        while (hull.size() && hull.back().at(hull.back().from) > x.at(hull.back().from))
        {
            hull.pop_back();
        }
        
        if (hull.empty()) hull.push_back(x);
        else if (x.at(MAX_X) < hull.back().at(MAX_X)) hull.push_back({x.a, x.b, intersect(hull.back(), x)});
    }
    
    long double query(long double x)
    {
        int l = 0, r = hull.size(), mid;
        while (l < r - 1)
        {
            mid = l + r >> 1;
            if (hull[mid].from <= x) l = mid;
            else r = mid;
        }
        
        assert(l < hull.size());
        long double ans = hull[l].at(x);
        // if (r != hull.size()) ans = std::max(ans, hull[r].at(x));
        return ans;
    }
};

struct CHT_MAX
{
    std::vector <Line> hull;
    void build(std::vector <std::pair <long double, long double>> &v)
    {
        std::sort(v.begin(), v.end(), [&](auto x, auto y)
        {
            return x.first < y.first;
        });
        
        for (const auto &x : v)
        {
            push({x.first, x.second, -(long double)MAX_X});
        }
    }
    
    void push(Line x)
    {
        x.from = -MAX_X;
        while (hull.size() && hull.back().at(hull.back().from) < x.at(hull.back().from))
        {
            hull.pop_back();
        }
        
        if (hull.empty()) hull.push_back(x);
        else if (x.at(MAX_X) > hull.back().at(MAX_X)) hull.push_back({x.a, x.b, intersect(hull.back(), x)});
    }
    
    long double query(long double x)
    {
        int l = 0, r = hull.size(), mid;
        while (l < r - 1)
        {
            mid = l + r >> 1;
            if (hull[mid].from <= x) l = mid;
            else r = mid;
        }
        
        assert(l < hull.size());
        long double ans = hull[l].at(x);
        // if (r != hull.size()) ans = std::max(ans, hull[r].at(x));
        return ans;
    }
};

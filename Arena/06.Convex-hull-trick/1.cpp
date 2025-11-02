#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 1e5 + 10;
const long long INF = 2e18 + 10;
const int MAX_X = 1e9 + 10;

int n, q;
std::vector<std::pair<long double, long double>> initials;

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

struct CHT_MIN
{
    std::vector<Line> hull;

    void build(std::vector<std::pair<long double, long double>>& v)
    {
        std::sort(v.begin(), v.end(), [&](const auto& x, const auto& y)
        {
            return x.first > y.first;
        });

        for(const auto& x : v)
        {
            push({x.first, x.second, -(long double)MAX_X});
        }
    }

    void push(Line x)
    {
        while(hull.size() && hull.back().at(hull.back().from) > x.at(hull.back().from))
        {
            hull.pop_back();
        }

        if(hull.empty()) hull.push_back(x);
        else if(x.at(MAX_X) < hull.back().at(MAX_X)) hull.push_back({x.a, x.b, intersect(hull.back(), x)});
    }

    long double binary(long double x)
    {
        int l = 0, r = hull.size();

        while(l + 1 < r)
        {
            int mid = (l + r) / 2;

            if(x < hull[mid].from) r = mid;
            else l = mid;
        }

        assert(l < hull.size());
        return hull[l].at(x);
    }
};

struct MST
{
    struct Node
    {
        CHT_MIN hull;

        Node() {}

        Node(std::pair<long double, long double> line)
        {
            hull.push({line.first, line.second, -(long double)MAX_X});
        }
    };

    Node tree[4 * MAXN];

    Node combine(const Node& x, const Node& y)
    {
        Node result;

        std::vector<std::pair<long double, long double>> v;

        for(auto& line : x.hull.hull)
        {
            v.push_back({line.a, line.b});
        }

        for(auto& line : y.hull.hull)
        {
            v.push_back({line.a, line.b});
        }

        result.hull.build(v);
        return result;
    }

    void build(int idx, int low, int high, std::vector<std::pair<long double, long double>>& v)
    {
        if(low == high)
        {
            tree[idx] = Node(v[low - 1]);
            return;
        }

        int mid = (low + high) / 2;

        build(2 * idx, low, mid, v);
        build(2 * idx + 1, mid + 1, high, v);

        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    long double query(int idx, int low, int high, int queryL, int queryR, long double x)
    {
        if(queryL > high || queryR < low)
        {
            return +(long double)INF;
        }
        else if(queryL <= low && high <= queryR)
        {
            return tree[idx].hull.binary(x);
        }

        int mid = (low + high) / 2;

        return std::min(query(2 * idx, low, mid, queryL, queryR, x),
                        query(2 * idx + 1, mid + 1, high, queryL, queryR, x));
    }

    void build(std::vector<std::pair<long double, long double>> &v)
    {
        build(1, 1, n, v);
    }

    long long query(int l, int r, long double x)
    {
        return (long long)query(1, 1, n, l, r, x);
    }
};

MST tree;

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        int b, a;
        std::cin >> b >> a;
        initials.push_back({a, b});
    }

    tree.build(initials);

    std::cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        int l, r, x;
        std::cin >> l >> r >> x;
        std::cout << tree.query(l, r, x - 1) << "\n";
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
}
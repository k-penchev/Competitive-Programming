#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 5 * 1e5 + 10;
const int LOG = 20;
const long long INF = 1e18;
const int MAX_X = 1e9;

int n;
int a[MAXN];
int left[MAXN], right[MAXN];
long long dp[MAXN];

struct Sparse
{
    int table[MAXN][LOG];
    int log[MAXN];

    //0 -> min , 1 -> max
    int f(int x, int y, bool type)
    {
        if(type == 0) return std::min(x, y);
        else return std::max(x, y);
    }

    void build(int * arr, bool type)
    {
        log[1] = 0;
        for(int i = 2 ; i <= n ; ++i)
        {
            log[i] = log[i / 2] + 1;
        }

        for(int i = 1 ; i <= n ; ++i)
        {
            table[i][0] = arr[i];
        }

        for(int j = 1 ; (1 << j) <= n ; ++j)
        {
            for(int i = 1 ; i + (1 << j) - 1 <= n ; ++i)
            {
                table[i][j] = f(table[i][j - 1], table[i + (1 << (j - 1))][j - 1], type);
            }
        }
    }

    int query(int l, int r, bool type)
    {
        int j = log[r - l + 1];
        return f(table[l][j], table[r - (1 << j) + 1][j], type);
    }
};

struct SegmentTree
{
    struct CHT
    {
        struct Line
        {
            long long a, b;
            long long from;

            long long at(long long x)
            {
                return a * x + b;
            }
        };

        long long intersect(const Line &x, const Line &y)
        {
            return ((y.b - x.b) / (x.a - y.a));
        }

        std::vector<Line> hull;
        void push(Line x)
        {
            x.from = +MAX_X;

            while(hull.size() && hull.back().at(hull.back().from) < x.at(hull.back().from))
            {
                hull.pop_back();
            }

            if(hull.empty()) hull.push_back(x);
            else if(x.at(MAX_X) > hull.back().at(MAX_X)) hull.push_back({x.a, x.b, intersect(hull.back(), x)});
        }

        long long query(long long x)
        {
            if(hull.empty()) return -INF;

            int l = 0, r = hull.size(); 

            while(l + 1 < r)
            {
                int mid = (l + r) / 2;

                if(hull[mid].from >= x) l = mid;
                else r = mid;
            }

            return hull[l].at(x);
        }
    };

    CHT tree[4 * MAXN];
    void update(int idx, int low, int high, int updatePos, long long a, long long b)
    {
        tree[idx].push({a, b});

        if(low == high)
        {
            return;
        }

        int mid = (low + high) / 2;

        if(updatePos <= mid) update(2 * idx, low, mid, updatePos, a, b);
        else update(2 * idx + 1, mid + 1, high, updatePos, a, b);
    }

    //it needs to be corrected
    long long query(int idx, int low, int high, long long queryPos)
    {
        if(low == high)
        {
            return tree[idx].query(queryPos);
        }

        int mid = (low + high) / 2;

        if(queryPos <= mid) query(2 * idx, low, mid, queryPos);
        else query(2 * idx + 1, mid + 1, high, queryPos);
    }

    void update(long long x, long long a, long long b)
    {
        update(1, 1, n, x, a, b);
    }

    long long query(long long x)
    {
        query(1, 1, n, x);
    }
};

Sparse tableMin;
Sparse tableMax;
SegmentTree segment[2];

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        left[i] = i + 1 - a[i];
        right[i] = i - 1 + a[i];
    }

    tableMin.build(right, 0);
    tableMax.build(left, 1);

    //the binary search step + segment tree
    for(int j = 1 ; j <= n ; ++j)
    {

    }

    //here I am not sure if it is correct
    dp[0] = 0;
    for(int i = 1 ; i <= n ; ++i)
    {
        int parity = i % 2;
        dp[i] = (i * i) / 4 + i + 1 + segment[parity].query(i);
    }

    std::cout << dp[n] << "\n";
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
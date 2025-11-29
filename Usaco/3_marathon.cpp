#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

const int MAXN = 100000 + 10;
const int INF = 2e9 + 10;

int n, m;
struct Point
{
    int x, y;

    inline friend int operator + (const Point &a, const Point &b)
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }
};

struct SegmentTree
{
    int seg[4 * MAXN];

    //0 -> sum, 1 -> max
    int f(int a, int b, bool type)
    {
        if(type == 0)
        {
            return a + b;
        }

        return std::max(a, b);
    }

    void build(int idx, int low, int high, int arr[], bool type)
    {
        if(low == high)
        {
            seg[idx] = arr[low];
            return;
        }

        int mid = (low + high) / 2;

        build(2 * idx, low, mid, arr, type);
        build(2 * idx + 1, mid + 1, high, arr, type);

        seg[idx] = f(seg[2 * idx], seg[2 * idx + 1], type);
    }

    void update(int idx, int low, int high, int pos, int value, bool type)
    {
        if(low == high)
        {
            seg[idx] = value;
            return;
        }

        int mid = (low + high) / 2;

        if(pos <= mid) update(2 * idx, low, mid, pos, value, type);
        else update(2 * idx + 1, mid + 1, high, pos, value, type);

        seg[idx] = f(seg[2 * idx], seg[2 * idx + 1], type);
    }

    int query(int idx, int low, int high, int qL, int qR, bool type)
    {
        if(qL > high || qR < low)
        {
            if(type == 0) return 0;
            else return -INF;
        }
        else if(qL <= low && high <= qR)
        {
            return seg[idx];
        }

        int mid = (low + high) / 2;
        return f(query(2 * idx, low, mid, qL, qR, type), 
                query(2 * idx, mid + 1, high, qL, qR, type), type);
    }

    void build(int arr[], bool type)
    {
        build(1, 1, n, arr, type);
    }

    void update(int pos, int val, bool type)
    {
        update(1, 1, n, pos, val, type);
    }

    int query(int l, int r, bool type)
    {
        if(l > r) return 0;
        return query(1, 1, n, l, r, type);
    }
};

int a[MAXN], b[MAXN];
Point point[MAXN];
SegmentTree segmentSUM;
SegmentTree segmentMAX;

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> point[i].x >> point[i].y;
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(i + 1 <= n) a[i] = point[i] + point[i + 1];
        if(i + 2 <= n) b[i] = (point[i] + point[i + 1]) + (point[i + 1] + point[i + 2]) - (point[i] + point[i + 2]);
    }

    segmentSUM.build(a, 0);
    segmentMAX.build(b, 1);

    for(int i = 1 ; i <= m ; ++i)
    {
        char type;
        int x, y, z;
        
        std::cin >> type;
        if(type == 'U')
        {
            std::cin >> x >> y >> z;
            point[x].x = y, point[x].y = z;

            if(x - 1 >= 1) segmentSUM.update(x - 1, point[x - 1] + point[x], 0);
            if(x + 1 <= n) segmentSUM.update(x, point[x] + point[x + 1], 0);

            for(int i = x - 2 ; i <= x ; ++i)
            {
                if(i >= 1 && i + 2 <= n)
                {
                    int gain = (point[i] + point[i + 1]) + (point[i + 1] + point[i + 2]) - (point[i] + point[i + 2]);
                    segmentMAX.update(i, gain, 1);
                }
            }
        }
        else
        {
            std::cin >> x >> y;
            std::cout << segmentSUM.query(x + 1, y - 1, 0) - segmentMAX.query(x + 1, y - 2, 1) << "\n";
        }
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
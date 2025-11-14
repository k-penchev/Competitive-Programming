#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <random>

const int MAXN = 5 * 1e5 + 10;

int n, k;

struct MST
{
    struct BIT
    {
        std::vector<int> bit;

        void init(int size)
        {
            bit.resize(size + 1, 0);
        }

        void update(int idx, int val)
        {
            idx++;
            for(; idx < bit.size() ; idx += idx & (-idx))
            {
                bit[idx] += val;
            }
        }

        int query(int idx)
        {
            idx++;
            int res = 0;
            for(; idx > 0 ; idx -= idx & (-idx))
            {
                res += bit[idx];
            }
            
            return res;
        }
    };

    std::vector<int> tree[4 * MAXN];
    BIT fenwick[4 * MAXN];

    void build(int idx, int low, int high, int arr[])
    {
        tree[idx].reserve(high - low + 1);
        fenwick[idx].init(high - low + 1);

        if(low == high)
        {
            tree[idx].push_back(arr[low]);
            return;
        }

        int mid = (low + high) / 2;
        build(2 * idx, low, mid, arr);
        build(2 * idx + 1, mid + 1, high, arr);

        int lPtr = 0, rPtr = 0;
        for(int i = 0 ; i < tree[2 * idx].size() + tree[2 * idx + 1].size() ; ++i)
        {
            if(lPtr == tree[2 * idx].size())
            {
                tree[idx].push_back(tree[2 * idx + 1][rPtr++]);
                continue;
            }

            if(rPtr == tree[2 * idx + 1].size())
            {
                tree[idx].push_back(tree[2 * idx][lPtr++]);
                continue;
            }

            if(tree[2 * idx][lPtr] <= tree[2 * idx + 1][rPtr])
            {
                tree[idx].push_back(tree[2 * idx][lPtr++]);
            }
            else
            {
                tree[idx].push_back(tree[2 * idx + 1][rPtr++]);
            }
        }
    }

    int findEqual(int node, int k)
    {
        int l = -1, r = tree[node].size();

        while(l + 1 < r)
        {
            int m = (l + r) / 2;

            if(tree[node][m] >= k) r = m;
            else l = m;
        }

        assert(tree[node][r] == k);
        return r;
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        fenwick[idx].update(findEqual(idx, val) , +1);

        if(low == high)
        {
            return;
        }

        int mid = (low + high) / 2;

        if(pos <= mid) update(2 * idx, low, mid, pos, val);
        else update(2 * idx + 1, mid + 1, high, pos, val);
    }

    int findSmaller(int node, int k)
    {
        int l = -1, r = tree[node].size();

        while(l + 1 < r)
        {
            int mid = (l + r) / 2;

            if(tree[node][mid] <= k) l = mid;
            else r = mid;
        }

        return fenwick[node].query(l);
    }

    int query(int idx, int low, int high, int queryL, int queryR, int val)
    {
        if(queryL > high || queryR < low)
        {
            return 0;
        }
        else if(queryL <= low && high <= queryR)
        {
            return findSmaller(idx, val);
        }

        int mid = (low + high) / 2;

        return query(2 * idx, low, mid, queryL, queryR, val) 
                + query(2 * idx + 1, mid + 1, high, queryL, queryR, val);
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }

    void update(int pos, int val)
    {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r, int val)
    {
        return query(1, 1, n, l, r, val);
    }
};

struct Point
{
    int x, y;
};

long long ans = 0;
Point point[MAXN];
int byY[MAXN];
int inY[MAXN];
int plus[MAXN];
int minus[MAXN];
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

    std::iota(byY + 1, byY + n + 1, 1);
    std::sort(byY + 1, byY + n + 1, [&](int a, int b)
    {
        return point[a].y < point[b].y;
    });

    for(int i = 1 ; i <= n ; ++i)
    {
        inY[byY[i]] = i;
        plus[i] = - point[byY[i]].x + point[byY[i]].y;
        minus[i] = - point[byY[i]].x - point[byY[i]].y;
    }

    mstPlus.build(plus);
    mstMinus.build(minus);
    for(int i = 1 ; i <= n ; ++i)
    {
        plus[i] = - point[i].x + point[i].y;
        minus[i] = - point[i].x - point[i].y;

        if(inY[i] != n) ans += mstPlus.query(inY[i] + 1, n, k + plus[i]);
        if(inY[i] != 1) ans += mstMinus.query(1, inY[i] - 1, k + minus[i]);
        mstPlus.update(inY[i], plus[i]);
        mstMinus.update(inY[i], minus[i]);
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
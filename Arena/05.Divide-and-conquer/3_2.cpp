#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 1e5 + 10;

int n;
int a[MAXN];
int byIndex[MAXN];

struct MST
{
    struct BIT
    {
        std::vector<int> bit;

        void init(int sz)
        {
            bit.resize(sz + 1, 0);
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

        int querySmaller(int idx)
        {
            return query(idx - 1);
        }

        int queryBigger(int idx)
        {
            return query(bit.size() - 2) - query(idx - 1);
        }
    };

    std::vector<int> tree[4 * MAXN];
    BIT fenwick[4 * MAXN];

    void build(int idx, int low, int high, int * arr)
    {
        fenwick[idx].init(high - low + 1);
        tree[idx].reserve(high - low + 1);

        if(low == high)
        {
            tree[idx].push_back(arr[low]);
            fenwick[idx].update(0, +1);
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

        for(int i = 0 ; i < tree[idx].size() ; ++i)
        {
            fenwick[idx].update(i, +1);
        }
    }

    int findEqual(const std::vector<int> &v, int k)
    {
        int l = -1, r = v.size();

        while(l + 1 < r)
        {
            int m = (l + r) / 2;

            if(v[m] >= k) r = m;
            else l = m;
        }

        assert(v[r] == k);
        return r;
    }

    void update(int idx, int low, int high, int value, int pos)
    {
        fenwick[idx].update(findEqual(tree[idx], value), -1);
        if(low == high)
        {
            return;
        }

        int mid = (low + high) / 2;
        if(pos <= mid) update(2 * idx, low, mid, value, pos);
        else update(2 * idx + 1, mid + 1, high, value, pos);
    }

    int getAns(int node, int k, bool findLess)
    {
        int l = -1, r = tree[node].size();

        while(l + 1 < r)
        {
            int m = (l + r) / 2;

            if(tree[node][m] >= k) r = m;
            else l = m;
        }

        if(findLess)
        {
            return fenwick[node].querySmaller(r);
        }
        else
        {
            return fenwick[node].queryBigger(r);
        }
    }

    int query(int idx, int low, int high, int queryL, int queryR, int val, bool findLess)
    {
        if(queryL > high || queryR < low)
        {
            return 0;
        }
        else if(queryL <= low && high <= queryR)
        {
            return getAns(idx, val, findLess);
        }

        int mid = (low + high) / 2;
        return query(2 * idx, low, mid, queryL, queryR, val, findLess)
               + query(2 * idx + 1, mid + 1, high, queryL, queryR, val, findLess);
    }

    void build(int * arr)
    {
        build(1, 1, n, arr);
    }

    void update(int value, int pos)
    {
        update(1, 1, n, value, pos);
    }

    int query(int l, int r, int val, bool findLess)
    {
        return query(1, 1, n, l, r, val, findLess);
    }
};

MST tree;
MST::BIT inversions;
long long ans = 0;

void solve()
{
    std::cin >> n;
    
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        byIndex[a[i]] = i;
    }

    inversions.init(n);
    for(int i = n ; i >= 1 ; --i)
    {
        ans += inversions.querySmaller(a[i] - 1);
        inversions.update(a[i] - 1, +1);
    }

    std::cout << ans << " ";
    tree.build(a);
    for(int i = 1 ; i <= n - 2 ; ++i)
    {
        int x;
        std::cin >> x;

        int cnt = 0;
        if(byIndex[x] - 1 >= 1) cnt += tree.query(1, byIndex[x] - 1, x, false);
        if(byIndex[x] + 1 <= n) cnt += tree.query(byIndex[x] + 1, n, x, true);
        tree.update(x, byIndex[x]);

        ans -= cnt;
        std::cout << ans << " ";
    }

    std::cout << "\n";
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
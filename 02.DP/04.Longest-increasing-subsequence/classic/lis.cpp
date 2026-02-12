/*
    To find LDS, just negate the values.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

const int MAXN = 100000 + 10;
const int INF = 1e9 + 10;

int n;
struct SegmentTree
{
    int tree[4 * MAXN];

    void update(int node, int l, int r, int queryPos, int queryVal)
    {
        if(l == r)
        {
            tree[node] = std::max(tree[node], queryVal);
            return;
        }

        int mid = l + r >> 1;
        if(queryPos <= mid) update(2*node, l, mid, queryPos, queryVal);
        else update(2*node + 1, mid + 1, r, queryPos, queryVal);
        tree[node] = std::max(tree[2*node], tree[2*node + 1]);
    }

    int query(int node, int l, int r, int queryL, int queryR)
    {
        if(queryL <= l && r <= queryR)
        {
            return tree[node];
        }

        int res = 0;
        int mid = l + r >> 1;
        if(queryL <= mid) res = std::max(res, query(2*node, l, mid, queryL, queryR));
        if(mid + 1 <= queryR) res = std::max(res, query(2*node + 1, mid + 1, r, queryL, queryR));
        return res;
    }

    void update(int pos, int val)
    {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
};

int a[MAXN];
int b[MAXN];
int dp[MAXN];
SegmentTree tree;
std::map<int, int> map;

void solve()
{
    int cnt = 1;
    std::sort(b + 1, b + n + 1);
    for(int i = 1 ; i <= n ; ++i)
    {
        map[b[i]] = cnt;
        if(i != n && b[i] != b[i + 1]) cnt += 1;
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        dp[i] = (map[a[i]] == 1 ? 1 : tree.query(1, map[a[i]] - 1) + 1); //strict LIS
        //dp[i] = (map[a[i]] == 1 ? 1 : tree.query(1, map[a[i]]) + 1); --> non-strict LIS
        tree.update(map[a[i]], dp[i]);
    }
}

void input()
{
    std::cin >> n;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        b[i] = a[i];
    }   
}

void output()
{
    int lis = 0;
    for(int i = 1 ; i <= n ; ++i)
    {
        lis = std::max(lis, dp[i]);
    }

    std::cout << lis << "\n";
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
    input();
    solve();
    output();
    return 0;
}
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

typedef long long llong;
const int MAXN = 1000000 + 10;
const int INF  = 1e9;

int n;
struct MST
{
    std::vector <int> tree[4*MAXN];
    void build(int l, int r, int node, const std::vector <int> &v)
    {
        if (l == r)
        {
            tree[node].push_back(v[l]);
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2*node, v);
        build(mid + 1, r, 2*node + 1, v);

        int lPtr = 0, rPtr = 0;
        tree[node].reserve(r - l + 1);
        for (int i = l ; i <= r ; ++i)
        {
            if (lPtr == tree[2*node].size())
            {
                tree[node].push_back(tree[2*node + 1][rPtr++]);
                continue;
            }

            if (rPtr == tree[2*node + 1].size())
            {
                tree[node].push_back(tree[2*node][lPtr++]);
                continue;
            }

            if (tree[2*node][lPtr] < tree[2*node + 1][rPtr])
            {
                tree[node].push_back(tree[2*node][lPtr++]);
            } else
            {
                tree[node].push_back(tree[2*node + 1][rPtr++]);
            }
        }
    }

    int binary(int node, int val)
    {
        int l = -1, r = tree[node].size(), mid;
        while (l < r - 1)
        {
            mid = (l + r) / 2;
            if (tree[node][mid] < val) l = mid;
            else r = mid;
        }

        return r;
    }

    int query(int l, int r, int node, int queryL, int queryR, int queryVal)
    {
        if (queryL <= l && r <= queryR)
        {
            return binary(node, queryVal);
        }

        int ans = 0;
        int mid = (l + r) / 2;
        if (queryL <= mid) ans += query(l, mid, 2*node, queryL, queryR, queryVal);
        if (mid + 1 <= queryR) ans += query(mid + 1, r, 2*node + 1, queryL, queryR, queryVal);
        return ans;
    }

    void build(const std::vector <int> &v)
    {
        build(0, n - 1, 1, v);
    }

    int query(int l, int r, int val)
    {
        return query(0, n - 1, 1, l, r, val);
    }
};

int root;
int in[MAXN], out[MAXN];
std::vector <int> g[MAXN];
std::vector <int> tour;
MST tree;

void buildTour(int node)
{
    tour.push_back(node);
    in[node] = tour.size() - 1;
    for (const int &i : g[node])
    {
        buildTour(i);
    }

    out[node] = tour.size() - 1;
}

void solve()
{
    buildTour(root);
    tree.build(tour);

    llong ans = 0;
    for (int i = 1 ; i <= n ; ++i)
    {
        ans += tree.query(in[i], out[i], i);
    }

    std::cout << ans << '\n';
}

void input()
{
    int p;
    std::cin >> n;
    for (int i = 1 ; i <= n ; ++i)
    {
        std::cin >> p;
        if (p == 0)
        {
            root = i;
        } else
        {
            g[p].push_back(i);
        }
    }
}

void fastIO()
{
    std::ios_base :: sync_with_stdio(0);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
}

int main()
{
    fastIO();
    input();
    solve();

    return 0;
}
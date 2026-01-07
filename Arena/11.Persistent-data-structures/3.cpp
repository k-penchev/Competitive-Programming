#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 100000 + 10;
const int MAXLOG = 17;

int n, m;
int a[MAXN];
std::vector<int> g[MAXN];

namespace MST
{
    std::vector<int> tree[4 * MAXN];

    void build(int node, int l, int r, int arr[])
    {
        if(l == r)
        {
            tree[node].push_back(arr[l]);
            return;
        }

        int mid = l + r >> 1;
        build(2 * node, l, mid, arr);
        build(2 * node + 1, mid + 1, r, arr);

        int lPtr = 0, rPtr = 0;
        for(int i = 0 ; i < tree[2 * node].size() + tree[2 * node + 1].size() ; ++i)
        {
            if(lPtr == tree[2 * node].size())
            {
                tree[node].push_back(tree[2 * node + 1][rPtr++]);
                continue;
            }

            if(rPtr == tree[2 * node + 1].size())
            {
                tree[node].push_back(tree[2 * node][lPtr++]);
                continue;
            }

            if(tree[2 * node][lPtr] <= tree[2 * node + 1][rPtr])
            {
                tree[node].push_back(tree[2 * node][lPtr++]);
            }
            else
            {
                tree[node].push_back(tree[2 * node + 1][rPtr++]);
            }
        }
    }

    int binary(int node, int k)
    {
        int l = -1, r = tree[node].size();
        while(l + 1 < r)
        {
            int mid = l + r >> 1;
            if(tree[node][mid] <= k) l = mid;
            else r = mid;
        }
        return l + 1;
    }

    int query(int node, int l, int r, int queryL, int queryR, int queryVal)
    {
        if(queryL <= l && r <= queryR)
        {
            return binary(node, queryVal);
        }

        int res = 0;
        int mid = l + r >> 1;
        if(queryL <= mid) res += query(2 * node, l, mid, queryL, queryR, queryVal);
        if(mid + 1 <= queryR) res += query(2 * node + 1, mid + 1, r, queryL, queryR, queryVal);
        return res;
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }

    int query(int l, int r, int val)
    {
        return query(1, 1, n, l, r, val);
    }

    llong kth(std::vector<std::pair<int, int>> &v, int k)
    {
        llong l = -1, r = 1e18 + 1;
        while(l + 1 < r)
        {
            int mid = l + r >> 1;

            int cnt = 0;
            for(auto [intervalL, intervalR] : v)
            {
                cnt += query(intervalL, intervalR, mid);
            }

            if(cnt >= k) r = mid;
            else l = mid;
        }

        return r;
    }
};

namespace HLD
{
    int size[MAXN];
    int depth[MAXN];
    int parent[MAXN];
    int top[MAXN];
    int id[MAXN];
    int flat[MAXN];
    int counter = 1;

    void dfs(int node, int par, int dep)
    {
        parent[node] = par;
        depth[node] = dep;
        size[node] = 1;

        for(const int &to : g[node])
        {
            if(to == par) continue;

            dfs(to, node, dep + 1);
            size[node] += size[to];
        }
    }

    void decompose(int node, int par, int head)
    {
        id[node] = counter++;
        top[node] = head;

        int heavyChild = -1, heavyChildSize = -1;
        for(const int &to : g[node])
        {
            if(to == par) continue;

            if(size[to] > heavyChildSize)
            {
                heavyChild = to;
                heavyChildSize = size[to];
            }
        }

        if(heavyChild == -1) return;
        decompose(heavyChild, node, head);

        for(const int &to : g[node])
        {
            if(to == par || to == heavyChild) continue;
            decompose(to, node, to);
        }
    }

    void build()
    {
        dfs(1, -1, 0);
        decompose(1, -1, 1);

        for(int i = 1 ; i <= n ; ++i)
        {
            flat[id[i]] = a[i];
        }

        MST::build(flat);
    }

    llong query(int a, int b, int k)
    {
        std::vector<std::pair<int, int>> v;
        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]])
            {
                std::swap(a, b);
            }

            v.push_back({id[top[a]], id[a]});
            a = parent[top[a]];
        }

        if(depth[a] > depth[b])
        {
            std::swap(a, b);
        }

        v.push_back({id[a], id[b]});
        return MST::kth(v, k);
    }
};

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    HLD::build();
    for(int i = 1 ; i <= m ; ++i)
    {
        int u, v, k;
        std::cin >> u >> v >> k;
        std::cout << HLD::query(u, v, k) << "\n";
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
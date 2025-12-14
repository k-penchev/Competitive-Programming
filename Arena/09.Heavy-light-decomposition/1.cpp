#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

const int MAXN = 10000 + 10;

int t, n;
int a[MAXN], b[MAXN], w[MAXN];
std::vector<int> tree[MAXN];

namespace SegmentTree
{
    int seg[4 * MAXN];

    void build(int idx, int low, int high, int arr[])
    {
        if(low == high)
        {
            seg[idx] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * idx, low, mid, arr);
        build(2 * idx + 1, mid + 1, high, arr);

        seg[idx] = std::max(seg[2 * idx], seg[2 * idx + 1]);
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            seg[idx] = val;
            return;
        }

        int mid = (low + high) / 2;
        if(pos <= mid) update(2 * idx, low, mid, pos, val);
        else update(2 * idx + 1, mid + 1, high, pos, val);

        seg[idx] = std::max(seg[2 * idx], seg[2 * idx + 1]);
    }

    int query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            return INT_MIN;
        }
        else if(queryL <= low && high <= queryR)
        {
            return seg[idx];
        }

        int mid = (low + high) / 2;
        return std::max(query(2 * idx, low, mid, queryL, queryR),
                        query(2 * idx + 1, mid + 1, high, queryL, queryR));
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
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

namespace HLD
{
    int parent[MAXN], depth[MAXN], size[MAXN];
    int top[MAXN], id[MAXN], flat[MAXN], counter = 1;

    void dfs(int node, int par, int dp)
    {
        parent[node] = par;
        depth[node] = dp;
        size[node] = 1;

        for(const int &to : tree[node])
        {
            if(to == par) continue;

            dfs(to, node, dp + 1);
            size[node] += size[to];
        }
    }

    void decompose(int node, int par, int head)
    {
        top[node] = head;
        id[node] = counter++;

        int heavyChild = -1, heavyChildSize = -1;
        for(const int &to : tree[node])
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

        for(const int &to : tree[node])
        {
            if(to == par || to == heavyChild) continue;
            decompose(to, node, to);
        }
    }
    
    void build()
    {
        dfs(1, 0, 0);
        decompose(1, 0, 1);

        flat[id[1]] = INT_MIN;
        for(int i = 1 ; i <= n - 1 ; ++i)
        {
            int edge = (depth[a[i]] > depth[b[i]] ? a[i] : b[i]);
            flat[id[edge]] = w[i];
        }

        SegmentTree::build(flat);
    }

    void update(int i, int w)
    {
        int edge = (depth[a[i]] > depth[b[i]] ? a[i] : b[i]);
        SegmentTree::update(id[edge], w);
    }

    int query(int a, int b)
    {
        int res = INT_MIN;

        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]])
            {
                std::swap(a, b);
            }

            res = std::max(res, SegmentTree::query(id[top[a]], id[a]));
            a = parent[top[a]];
        }

        if(depth[a] > depth[b])
        {
            std::swap(a, b);
        }

        return std::max(res, SegmentTree::query(id[a] + 1, id[b]));
    }

};

void reset()
{
    HLD::counter = 1;
    for(auto& t : tree) t.clear();
}

void solve()
{
    std::cin >> t;

    for(int i = 1 ; i <= t ; ++i)
    {
        std::cin >> n;

        for(int j = 1 ; j <= n - 1 ; ++j)
        {
            std::cin >> a[j] >> b[j] >> w[j];
            tree[a[j]].push_back(b[j]);
            tree[b[j]].push_back(a[j]);
        }

        HLD::build();

        while(true)
        {
            int x, y;
            std::string type;
            std::cin >> type;

            if(type == "QUERY")
            {
                std::cin >> x >> y;
                std::cout << HLD::query(x, y) << "\n";
            }
            else if(type == "CHANGE")
            {
                std::cin >> x >> y;
                HLD::update(x, y);
            }
            else
            {
                break;
            }
        }

        reset();
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
    
    return 0;
}
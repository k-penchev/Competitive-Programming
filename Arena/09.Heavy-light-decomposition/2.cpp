#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

const int MAXN = 150000 + 10;

int n, k;
std::vector<int> tree[MAXN];

namespace SegmentTree
{
    int seg[4 * MAXN];

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            seg[idx] += val;
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
    int top[MAXN], id[MAXN], counter = 1;

    void dfs(int node, int par, int currDepth)
    {
        parent[node] = par;
        depth[node] = currDepth;
        size[node] = 1;

        for(const int &to : tree[node])
        {
            if(to == par) continue;

            dfs(to, node, currDepth + 1);
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
    }

    void update(int node, int val)
    {
        SegmentTree::update(id[node], val);
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

        return std::max(res, SegmentTree::query(id[a], id[b]));
    }
};

void solve()
{
    std::cin >> n >> k;

    for(int u = 2 ; u <= n ; ++u)
    {
        int v; std::cin >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    HLD::build();

    for(int i = 1 ; i <= k ; ++i)
    {
        int x, y, z;
        std::string type;

        std::cin >> type >> x >> y >> z;

        if(type == "k4i")
        {
            std::cout << 10 * x - HLD::query(y, z) << "\n";
        }
        else
        {
            HLD::update(y, z);
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
    
    return 0;
}
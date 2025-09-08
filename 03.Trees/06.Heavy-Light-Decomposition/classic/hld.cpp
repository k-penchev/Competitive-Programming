#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n, q;
int val[MAXN];
vector<vector<int>> tree(MAXN);

namespace SegmentTree
{
    int seg[4 * MAXN];

    void build(int idx, int low, int high, int v[])
    {
        if(low == high)
        {
            seg[idx] = v[low];
            return;
        }

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        build(l, low, mid, v);
        build(r, mid + 1, high, v);

        seg[idx] = max(seg[l], seg[r]);
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            seg[idx] = val;
            return;
        }

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        if(pos <= mid) update(l, low, mid, pos, val);
        else update(r, mid + 1, high, pos, val);

        seg[idx] = max(seg[l], seg[r]);
    }

    int query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low) return INT_MIN;
        else if(queryL <= low && high <= queryR) return seg[idx];

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        return max(query(l, low, mid, queryL, queryR), query(r, mid + 1, high, queryL, queryR));
    }

    void build(int v[])
    {
        build(1, 1, n, v);
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
    int depth[MAXN], siz[MAXN], parent[MAXN];
    int top[MAXN], id[MAXN], flat[MAXN], counter = 1;

    void dfs(int node, int par, int currDepth)
    {
        depth[node] = currDepth;
        parent[node] = par;
        siz[node] = 1;

        for(const int& child : tree[node])
        {
            if(child == par) continue;

            dfs(child, node, currDepth + 1);

            siz[node] += siz[child];
        }
    }

    void decompose(int node, int par, int head)
    {
        id[node] = counter++;
        top[node] = head;

        int heavy_child = -1, heavy_child_sz = -1;

        for(const int& child : tree[node])
        {
            if(child == par) continue;

            if(siz[child] > heavy_child_sz)
            {
                heavy_child_sz = siz[child];
                heavy_child = child;
            }
        }

        if(heavy_child == -1) return;
        decompose(heavy_child, node, head);

        for(const int& child : tree[node])
        {
            if(child == par || child == heavy_child) continue;
            decompose(child, node, child);
        }
    }

    void build()
    {
        dfs(1, 0, 0);

        top[0] = 0;
        depth[0] = -1;

        decompose(1, 0, 1);

        for(int i = 1 ; i <= n ; ++i)
        {
            flat[id[i]] = val[i];
        }

        SegmentTree::build(flat);
    }

    void update(int node, int val)
    {
        SegmentTree::update(id[node], val);
    }

    int query(int a, int b)
    {
        int ret = INT_MIN;

        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);
            
            ret = max(ret, SegmentTree::query(id[top[a]], id[a]));

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);

        ret = max(ret, SegmentTree::query(id[a], id[b]));

        return ret;
    }
};

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> val[i];
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    HLD::build();

    for(int i = 1 ; i <= q ; ++i)
    {
        int qType, x, y;
        cin >> qType >> x >> y;

        if(qType == 1)
        {
            HLD::update(x, y);
        }
        else
        {
            cout << HLD::query(x, y) << " ";
        }
    }

    cout << "\n";
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
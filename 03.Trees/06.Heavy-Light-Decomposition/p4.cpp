#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000 + 10;
const int INF = 1e9 + 10;

int n, m;
int a[MAXN], b[MAXN];
vector<vector<int>> tree(MAXN);

namespace SegmentTree
{
    int seg[4 * MAXN], lazy[4 * MAXN];

    void build()
    {
        fill(seg,  seg  + 4 * MAXN, INF);
        fill(lazy, lazy + 4 * MAXN, INF);
    }


    void push(int idx, int low, int high)
    {
        if(lazy[idx] == INF) return;

        seg[idx] = min(seg[idx], lazy[idx]);

        if(low != high)
        {
            lazy[2 * idx] = min(lazy[2 * idx], lazy[idx]);
            lazy[2 * idx + 1] = min(lazy[2 * idx + 1], lazy[idx]);
        }

        lazy[idx] = INF;
    }

    void update(int idx, int low, int high, int queryL, int queryR, int val)
    {
        push(idx, low, high);

        if(queryL > high || queryR < low) return;
        else if(queryL <= low && high <= queryR)
        {
            lazy[idx] = min(lazy[idx], val);
            push(idx, low, high);
            return;
        }

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        update(l, low, mid, queryL, queryR, val);
        update(r, mid + 1, high, queryL, queryR, val);

        seg[idx] = min(seg[l], seg[r]);
    }

    int query(int idx, int low, int high, int pos)
    {
        push(idx, low, high);              
        
        if (low == high) return seg[idx];

        int mid = (low + high) / 2;
        
        if (pos <= mid) return query(2*idx, low, mid, pos);
        else            return query(2*idx+1, mid+1, high, pos);
    }

    void update(int l, int r, int val)
    {
        update(1, 1, n, l, r, val);
    }

    int query(int pos)
    {   
        return query(1, 1, n, pos);
    }
};

namespace HLD
{
    int depth[MAXN], siz[MAXN], parent[MAXN];
    int top[MAXN], id[MAXN], counter = 1;

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

        int heavy_child = -1, heavy_child_siz = -1;

        for(const int& child : tree[node])
        {
            if(child == par) continue;

            if(siz[child] > heavy_child_siz)
            {
                heavy_child_siz = siz[child];
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

        depth[0] = top[0] = 0;

        decompose(1, 0, 1);

        SegmentTree::build();
    }

    void update(int a, int b, int c)
    {
        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);

            SegmentTree::update(id[top[a]], id[a], c);

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);

        SegmentTree::update(id[a] + 1, id[b], c);
    }

    int query(int a, int b)
    {
        if(depth[a] < depth[b]) swap(a, b);
        int res = SegmentTree::query(id[a]);

        return (res == INF ? -1 : res);
    }
};

void solve()
{
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);

    cin >> n >> m;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        cin >> a[i] >> b[i];
        tree[a[i]].push_back(b[i]);
        tree[b[i]].push_back(a[i]);
    }

    HLD::build();

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;

        HLD::update(a, b, w);
    }

    for(int i = 1 ; i <= n - 1; ++i)
    {
        cout << HLD::query(a[i], b[i]) << "\n";
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
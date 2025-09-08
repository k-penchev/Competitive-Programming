#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int NINF = -1e9;

int n, q;
vector<vector<int>> tree(MAXN);

namespace SegmentTree
{
    int seg[4 * MAXN], lazy[4 * MAXN];

    void build()
    {
        fill(seg, seg + 4 * MAXN, 0);
        fill(lazy, lazy + 4 * MAXN, 0);
    }

    void push(int idx, int low, int high)
    {
        if(lazy[idx])
        {
            seg[idx] += lazy[idx];

            if(low != high)
            {
                lazy[2 * idx] += lazy[idx];
                lazy[2 * idx + 1] += lazy[idx];
            }

            lazy[idx] = 0;
        }
    }

    void update(int idx, int low, int high, int queryL, int queryR, int val)
    {
        push(idx, low, high);

        if(queryL > high || queryR < low) return;
        else if(queryL <= low && high <= queryR)
        {
            lazy[idx] += val;
            push(idx, low, high);
            return;
        }

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        update(l, low, mid, queryL, queryR, val);
        update(r, mid + 1, high, queryL, queryR, val);

        seg[idx] = max(seg[l], seg[r]);
    }

    int query(int idx, int low, int high, int queryL, int queryR)
    {
        push(idx, low, high);

        if(queryL > high || queryR < low) return NINF;
        else if(queryL <= low && high <= queryR) return seg[idx];

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        return max(query(l, low, mid, queryL, queryR), query(r, mid + 1, high, queryL, queryR));
    }

    void update(int l, int r, int val)
    {
        update(1, 1, n, l, r, val);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
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

        int h_ch = -1, h_ch_siz = -1;

        for(const int& child : tree[node])
        {
            if(child == par) continue;

            if(siz[child] > h_ch_siz)
            {
                h_ch_siz = siz[child];
                h_ch = child;
            }
        }

        if(h_ch == -1) return;
        decompose(h_ch, node, head);

        for(const int& child : tree[node])
        {
            if(child == par || child == h_ch) continue;
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

    void update(int node, int val)
    {
        SegmentTree::update(id[node], id[node] + siz[node] - 1, val);
    }

    int query(int a, int b)
    {
        int ret = NINF;

        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);

            ret = max(ret, SegmentTree::query(id[top[a]], id[a]));

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);

        ret = max(ret, SegmentTree::query(id[a], id[b]));

        return (ret == NINF ? 0 : ret);
    }
};

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    HLD::build();

    cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        string qType;
        int x, y;

        cin >> qType >> x >> y;

        if(qType == "add")
        {
            HLD::update(x, y);
        }
        else
        {
            cout << HLD::query(x, y) << "\n";
        }
    }
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
}
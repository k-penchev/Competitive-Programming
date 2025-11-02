#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int INF = 1e9;

int n, q;
vector<vector<int>> tree(MAXN);

namespace SegmentTree
{
    int seg[4 * MAXN];

    void build(int idx, int low, int high)
    {
        if(low == high)
        {
            seg[idx] = +INF;;
            return;
        }

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        build(l, low, mid);
        build(r, mid + 1, high);

        seg[idx] = min(seg[l], seg[r]);
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

        seg[idx] = min(seg[l], seg[r]);
    }

    int query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low) return INF;
        else if(queryL <= low && high <= queryR) return seg[idx];

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        return min(query(l, low, mid, queryL, queryR), query(r, mid + 1, high, queryL, queryR));
    }

    void build()
    {
        build(1, 1, n);
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
    int top[MAXN], id[MAXN], rev_id[MAXN], color[MAXN], counter = 1;

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
        rev_id[id[node]] = node;
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

    void update(int node)
    {
        if(color[node] == 0)
        {
            SegmentTree::update(id[node], id[node]);
        }
        else
        {
            SegmentTree::update(id[node], +INF);
        }

        color[node] ^= 1;
    }

    int query(int node)
    {
        vector<pair<int,int>> segs;
        
        while (top[node] != top[1])
        {
            segs.push_back({id[top[node]], id[node]}); 
            node = parent[top[node]];
        }
        
        segs.push_back({id[1], id[node]});

        
        for (int i = segs.size() - 1 ; i >= 0 ; --i)
        {
            auto [L, R] = segs[i];
            int pos = SegmentTree::query(L, R); 
            if (pos != INF) return rev_id[pos];     
        }

        return -1;
    }

};

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n - 1; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    HLD::build();

    for(int i = 1 ; i <= q ; ++i)
    {
        int qType, x;
        cin >> qType >> x;

        if(qType == 0)
        {
            HLD::update(x);
        }
        else
        {
            cout << HLD::query(x) << "\n";
        }
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
    
    return 0;
}
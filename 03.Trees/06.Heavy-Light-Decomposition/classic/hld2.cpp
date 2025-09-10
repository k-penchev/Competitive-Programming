#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int INF = +1e9;

int n, q;
int color[MAXN];
vector<vector<int>> tree(MAXN);

namespace SegmentTree
{   
    int seg[4 * MAXN];

    void build()
    {   
        fill(seg, seg + 4 * MAXN, +INF);
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
    int top[MAXN], id[MAXN], rev_id[MAXN], counter = 1;

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
        int a = node, b = 1;

        vector<pair<int, int>> segs;

        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);

            segs.push_back({id[top[a]], id[a]});

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);

        segs.push_back({id[a], id[b]});

        for (int i = segs.size() - 1 ; i >= 0 ; --i)
        {
            auto [L, R] = segs[i];

            int best = SegmentTree::query(L, R);
            if(best != INF) return rev_id[best];
        }

        return -1;
    }
};

void solve()
{
    
    cin >> n >> q;

    for(int i = 1 ; i <= n - 1; ++i)
    {
        int a, b;
        cin >> a >> b;

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
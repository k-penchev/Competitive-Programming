#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int NINF = -1e9;

int T, N;
int a[MAXN], b[MAXN], w[MAXN];
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
        if(queryL > high || queryR < low) return NINF;
        else if(queryL <= low && high <= queryR) return seg[idx];

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        return max(query(l, low, mid, queryL, queryR), query(r, mid + 1, high, queryL, queryR));
    }

    void build(int v[])
    {
        build(1, 1, N, v);
    }

    void update(int pos, int val)
    {
        update(1, 1, N, pos, val);
    }

    int query(int l, int r)
    {
        return query(1, 1, N, l, r);
    }

    void clear()
    {
        fill(seg, seg + 4 * MAXN, 0);
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

        flat[id[1]] = NINF;

        for(int i = 1 ; i <= N - 1 ; ++i)
        {
            int edge = (depth[a[i]] > depth[b[i]] ? a[i] : b[i]);
            flat[id[edge]] = w[i];
        }

        SegmentTree::build(flat);
    }

    void update(int edge_id, int new_w)
    {
        int f = a[edge_id], s = b[edge_id];
        int node = (depth[f] > depth[s] ? f : s);

        SegmentTree::update(id[node], new_w);
    }

    int query(int a, int b)
    {
        int res = NINF;

        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);

            res = max(res, SegmentTree::query(id[top[a]], id[a]));

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);

        res = max(res, SegmentTree::query(id[a] + 1, id[b]));

        return res;
    }

    void clear()
    {
        fill(a + 1, a + N + 1, 0);
        fill(b + 1, b + N + 1, 0);
        fill(w + 1, w + N + 1, 0);

        for(auto& t : tree) t.clear();

        fill(depth + 1, depth + N + 1, 0);
        fill(siz + 1, siz + N + 1, 0);
        fill(parent + 1, parent + N + 1, 0);
        fill(top + 1, top + N + 1, 0);
        fill(id + 1, id + N + 1, 0);
        fill(flat + 1, flat + N + 1, 0);
        
        counter = 1;
        
        SegmentTree::clear();
    }
};

void solve()
{
    cin >> T;

    for(int rep = 1 ; rep <= T ; ++rep)
    {
        cin >> N;

        for(int i = 1 ; i <= N - 1; ++i)
        {
            cin >> a[i] >> b[i] >> w[i];

            tree[a[i]].push_back(b[i]);
            tree[b[i]].push_back(a[i]);
        }

        HLD::build();

        string qType;
        int x, y;

        while(true)
        {
            cin >> qType;

            if(qType == "CHANGE")
            {
                cin >> x >> y;  
                HLD::update(x, y);
            }
            else if(qType == "QUERY")
            {
                cin >> x >> y;
                cout << HLD::query(x, y) << "\n";
            }
            else break;
        }

        HLD::clear();
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
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, q;
vector<vector<int>> tree(MAXN);
int color[MAXN];

struct Node
{
    int l_color;
    int r_color;
    int breaks;
    int lazy_color;
    bool empty;

    Node()
    {
        l_color = r_color = 0;
        breaks = 0;
        lazy_color = 0;
        empty = true;
    }

    Node(int c)
    {
        l_color = r_color = c;
        breaks = 0;
        lazy_color = 0;
        empty = false;
    }
};

Node reverse(Node node)
{
    swap(node.l_color, node.r_color);
    return node;
}

Node combine(const Node& left, const Node& right)
{
    if(left.empty) return right;
    if(right.empty) return left;

    Node res;

    res.l_color = left.l_color;
    res.r_color = right.r_color;
    res.breaks = left.breaks + right.breaks + (left.r_color != right.l_color ? 1 : 0);
    res.empty = false;

    return res;
}

struct SegmentTree
{
    Node seg[4 * MAXN];

    void build(int idx, int low, int high, int v[])
    {
        if(low == high)
        {
            seg[idx] = Node(v[low]);
            return;
        }

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        build(l, low, mid, v);
        build(r, mid + 1, high, v);

        seg[idx] = combine(seg[l], seg[r]);
    }   
    
    void push(int idx, int low, int high)
    {
        if(seg[idx].lazy_color)
        {
            seg[idx].l_color = seg[idx].r_color = seg[idx].lazy_color;
            seg[idx].breaks = 0;
            
            if(low != high)
            {
                seg[2 * idx].lazy_color = seg[idx].lazy_color;
                seg[2 * idx + 1].lazy_color = seg[idx].lazy_color;
            }

            seg[idx].lazy_color = 0;
        }

    }

    void update(int idx, int low, int high, int queryL, int queryR, int new_color)
    {
        push(idx, low, high);
        if(queryL > high || queryR < low) return;
        else if(queryL <= low && high <= queryR)
        {
            seg[idx].lazy_color = new_color;
            push(idx, low, high);
            return;
        }


        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        update(l, low, mid, queryL, queryR, new_color);
        update(r, mid + 1, high, queryL, queryR, new_color);

        seg[idx] = combine(seg[l], seg[r]);
    }

    Node query(int idx, int low, int high, int queryL, int queryR)
    {
        push(idx, low, high);

        if(queryL > high || queryR < low) return Node();
        else if(queryL <= low && high <= queryR) return seg[idx];

        int mid = (low + high) / 2;
        int l = 2 * idx;
        int r = 2 * idx + 1;

        Node le, ri;

        le = query(l, low, mid, queryL, queryR);
        ri = query(r, mid + 1, high, queryL, queryR);

        return combine(le, ri);
    }

    void build(int v[])
    {
        build(1, 1, n, v);
    }

    void update(int l, int r, int c)
    {
        update(1, 1, n, l, r, c);
    }

    Node query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
};

SegmentTree seg;

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
        
        depth[0] = top[0] = 0;

        decompose(1, 0, 1);

        for(int i = 1 ; i <= n ; ++i)
        {
            flat[id[i]] = color[i];
        }

        seg.build(flat);
    }

    void update1(int a, int b, int new_color)
    {
        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);
            seg.update(id[top[a]], id[a], new_color);

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);
        seg.update(id[a], id[b], new_color);
    }

    void update2(int a, int new_color)
    {
        seg.update(id[a], id[a] + siz[a] - 1, new_color);
    }

    int query(int a, int b)
    {
        Node le, ri;

        while(top[a] != top[b])
        {
            if(depth[top[a]] >= depth[top[b]])
            {
                Node cur = seg.query(id[top[a]], id[a]);
                
                cur = reverse(cur);
                le = combine(le, cur);

                a = parent[top[a]];
            }
            else
            {
                Node cur = seg.query(id[top[b]], id[b]);
                
                ri = combine(cur, ri);

                b = parent[top[b]];
            }
        }

        if(depth[a] >= depth[b])
        {
            Node cur = seg.query(id[b], id[a]);

            cur = reverse(cur);
            le = combine(le, cur);
        }
        else
        {
            ri = combine(seg.query(id[a], id[b]), ri);
        }

        return combine(le, ri).breaks;
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

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> color[i];
    }

    HLD::build();

    cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        int qType, a, b, c;

        cin >> qType;

        if(qType == 1)
        {
            cin >> a >> b >> c;
            HLD::update1(a, b, c);
        }
        else if(qType == 2)
        {
            cin >> a >> c;
            HLD::update2(a, c);
        }
        else
        {
            cin >> a >> b;
            cout << HLD::query(a, b) << "\n";
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
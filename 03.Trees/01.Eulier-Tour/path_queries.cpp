#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;

int n, q;
int val[MAXN];
vector<vector<int>> tree(MAXN);

struct SegmentTree
{
    int seg[4 * MAXN];
    int lazy[4 * MAXN];

    void push(int idx, int low, int high)
    {
        if (lazy[idx] == 0) return;            

        int len = high - low + 1;
        
        if (len & 1) seg[idx] ^= lazy[idx];     

        if (low != high)
        {                      
            lazy[2*idx]     ^= lazy[idx];
            lazy[2*idx + 1] ^= lazy[idx];
        }
        
        lazy[idx] = 0;
    }

    void update(int idx, int low, int high, int queryL, int queryR, int val)
    {
        push(idx, low, high);

        if(queryL > high || queryR < low)
        {
            return;
        }
        else if(queryL <= low && high <= queryR)
        {
            lazy[idx] ^= val;
            push(idx, low, high);
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        update(left, low, mid, queryL, queryR, val);
        update(right, mid + 1, high, queryL, queryR, val);

        seg[idx] = seg[left] ^ seg[right];
    }

    int query(int idx, int low, int high, int pos)
    {   
        push(idx, low, high);

        if(low == high)
        {
            return seg[idx];
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        int answer = 0;

        if(pos <= mid)
        {
            answer ^= query(left, low, mid, pos);
        }
        else
        {
            answer ^= query(right, mid + 1, high, pos);
        }

        return answer;
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

SegmentTree seg;
int in[MAXN], out[MAXN], depth[MAXN], par[MAXN][22];
int timer = 0;

void build_euler(int node, int parent, int currentDepth)
{
    in[node] = ++timer;
    depth[node] = currentDepth;
    
    par[node][0] = parent;

    for(int i = 1; i <= 21 ; ++i)
    {
        par[node][i] = par[par[node][i - 1]][i - 1];
    }

    for(int& to : tree[node])
    {
        if(to == parent) continue;
        build_euler(to, node, currentDepth + 1);
    }

    out[node] = timer;
}

bool is_ancestor(int a, int b)
{
    return (in[a] <= in[b] && out[a] >= out[b]);
}

int LCA(int a, int b)
{
    if(is_ancestor(a, b)) return a;

    for(int i = 21 ; i >= 0 ; --i)
    {
        if(par[a][i] > 0 && !is_ancestor(par[a][i], b))
        {
            a = par[a][i];
        }
    };

    return par[a][0];
}

int query(int a, int b)
{
    if(depth[a] < depth[b]) swap(a, b);

    int toA = seg.query(in[a]);
    int toB = seg.query(in[b]);

    int lca = LCA(a, b);

    return toA ^ toB ^ val[lca];
}

void solve()
{
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);

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

    build_euler(1, 0, 1);;

    for(int i = 1 ; i <= n ; ++i)
    {
        seg.update(in[i], out[i], val[i]);
    }

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int qType, a, b;

        cin >> qType >> a >> b;

        if(qType == 1)
        {
            int delta = b ^ val[a];
            val[a] = b;
            seg.update(in[a], out[a], delta);
        }
        else
        {
            cout << query(a, b) << "\n";
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
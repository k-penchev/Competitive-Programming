#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;

int n, q;
int val[MAXN];
vector<vector<int>> tree(MAXN);

struct SegmentTree
{
    int seg[4 * MAXN];

    void build(int idx, int low, int high, vector<int>& v)
    {
        if(low == high)
        {
            seg[idx] = v[low];
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid, v);
        build(right, mid + 1, high, v);

        seg[idx] = seg[left] + seg[right];
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            seg[idx] = val;
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        if(pos <= mid)
        {
            update(left, low, mid, pos, val);
        }
        else
        {
            update(right, mid + 1, high, pos, val);
        }

        seg[idx] = seg[left] + seg[right];
    }

    int query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            return 0;
        }
        else if(queryL <= low && high <= queryR)
        {
            return seg[idx];
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        int le = query(left, low, mid, queryL, queryR);
        int ri = query(right, mid + 1, high, queryL, queryR);

        return le + ri;
    }

    void build(vector<int>& v)
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

SegmentTree seg;

int timer = 0;
int in[MAXN], out[MAXN];
//vector<int> tour;

void build_euler(int node, int par)
{
    in[node] = ++timer;
    //tour.push_back(node);

    for(const int& to : tree[node])
    {
        if(to == par) continue;
        build_euler(to, node);
    }

    out[node] = timer;
}

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> val[i];
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int x, y;
        cin >> x >> y;

        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    build_euler(1, 0);

    vector<int> flat(n + 1);

    for (int u = 1; u <= n; ++u)
    {
        flat[in[u]] = val[u];   
    }

    seg.build(flat);

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int qType, x, y;
        cin >> qType;

        if(qType == 1)
        {
            cin >> x >> y;
            seg.update(in[x], y);
        }
        else
        {
            cin >> x;
            cout << seg.query(in[x], out[x]) << "\n";
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
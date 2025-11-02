#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;

int n, q;
vector<vector<int>> tree(MAXN);
int in[MAXN], out[MAXN], timer = 0;
set<pair<int, int>> color[MAXN];

struct SegmentTree
{
    int seg[4 * MAXN], lazy[4 * MAXN];

    void push(int idx, int low, int high)
    {
        if(lazy[idx])
        {
            seg[idx] += lazy[idx] * (high - low + 1);

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

        if(queryL > high || queryR < low)
        {
            return;
        }
        else if(queryL <= low && high <= queryR)
        {
            lazy[idx] += val;
            push(idx, low, high);
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;
    
        update(left, low, mid, queryL, queryR, val);
        update(right, mid + 1, high, queryL, queryR, val);

        seg[idx] = seg[left] + seg[right];
    }

    int query(int idx, int low, int high, int queryL, int queryR)
    {
        push(idx, low, high);

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
    
        int le, ri;

        le = query(left, low, mid, queryL, queryR);
        ri = query(right, mid + 1, high, queryL, queryR);

        return le + ri;
    }

    void update(int l, int r, int k)
    {
        update(1, 1, n, l, r, k);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
};

SegmentTree seg;

void update(int x, int y)
{
    auto& S = color[y];

    int L = in[x], R = out[x];
    int newL = L, newR = R;

    auto it = S.lower_bound({L + 1, INT_MIN});

    if(it != S.begin()) --it;

    while(it != S.end())
    {
        auto [currL, currR] = (*it);

        if(currR < L)
        {
            ++it; continue;
        } 

        if(currL > R) break;

        int interL = max(currL, L);
        int interR = min(currR, R);

        seg.update(interL, interR, -1);

        newL = min(newL, currL);
        newR = max(newR, currR);

        auto nxt = next(it);
        S.erase(it);
        it = nxt;
    }

    seg.update(L, R, +1);
    S.insert({newL, newR});
}

int query(int x)
{
    return seg.query(in[x], out[x]);
}

void euler(int node, int par)
{
    in[node] = ++timer;

    for(int& to : tree[node])
    {
        if(to == par) continue;
        euler(to, node);
    }

    out[node] = timer;
}

void solve()
{
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);

    cin >> n >> q;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    euler(1, 0);

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int qType, x, y; cin >> qType;

        if(qType == 1)
        {
            cin >> x >> y;
            update(x, y);
        }   
        else
        {
            cin >> x;
            cout << query(x) << "\n";
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
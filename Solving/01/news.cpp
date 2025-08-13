#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;

int n, q;
vector<vector<int>> tree(MAXN);
int b[MAXN];

int timer = 0;
int in[MAXN], out[MAXN], depth[MAXN];
vector<int> tour;

struct Node
{
    vector<int> v;
};

struct MST
{
    Node seg[4 * MAXN];

    Node combine(const Node& left, const Node& right)
    {
        
        Node res;

        int lPtr = 0, rPtr = 0;
        res.v.reserve(left.v.size() + right.v.size());

        for(int i = 1 ; i <= left.v.size() + right.v.size() ; ++i)
        {
            if(lPtr == left.v.size())
            {
                res.v.push_back(right.v[rPtr++]);
                continue;
            }

            if(rPtr == right.v.size())
            {
                res.v.push_back(left.v[lPtr++]);
                continue;
            }

            if(left.v[lPtr] < right.v[rPtr])
            {
                res.v.push_back(left.v[lPtr++]);
            }
            else
            {
                res.v.push_back(right.v[rPtr++]);
            }
        }

        return res;
    }

    void build(int idx, int low, int high)
    {
        if(low == high)
        {
            seg[idx].v = {};

            if(b[tour[low]])
            {
                seg[idx].v.push_back(depth[tour[low]]);
            }

            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid);
        build(right, mid + 1, high);

        seg[idx] = combine(seg[left], seg[right]);
    }

    int binary(Node& node, int k)
    {
        int lPtr = -1, rPtr = node.v.size();

        while(rPtr > lPtr + 1)
        {
            int mid = (lPtr + rPtr) / 2;

            if(node.v[mid] > k)
            {
                rPtr = mid;
            }
            else
            {
                lPtr = mid;
            }
        }

        return lPtr + 1;
    }

    int query(int idx, int low, int high, int queryL, int queryR, int k)
    {

        if(queryL > high || queryR < low)
        {
            return 0;
        }
        else if(queryL <= low && high <= queryR)
        {
            return binary(seg[idx], k);
        }
        
        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        return query(left, low, mid, queryL, queryR, k) + query(right, mid + 1, high, queryL, queryR, k);
    }


    void build()
    {
        build(1, 0, n - 1);
    }

    int query(int l, int r, int k)
    {
        return query(1, 0, n - 1, l, r, k);
    }
};

MST seg;

void dfs(int node, int par, int d)
{
    in[node] = timer++;
    depth[node] = d;

    tour.push_back(node);
    
    for(int to : tree[node])
    {
        if(to == par) continue;
        
        dfs(to, node, d + 1);

    }

    out[node] = timer - 1;
}

void solve()
{

    cin >> n;

    int f, t;

    for(int i = 0 ; i < n - 1 ; ++i)
    {
        cin >> f >> t; --f, --t;

        tree[f].push_back(t);
        tree[t].push_back(f);
    }

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> b[i];
    }


    dfs(0, -1, 0);
    
    seg.build();

    cin >> q;

    int type, x, k;

    for(int i = 0 ; i < q ; ++i)
    {
        cin >> type >> x >> k; --x;

        if(type == 1)
        {
            
        }
        else
        {
            k = depth[x] + k;
            cout << seg.query(in[x], out[x], k) << "\n";
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
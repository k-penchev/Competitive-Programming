#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int MAXLOG = 20;

int n, q;
vector<vector<int>> tree(MAXN);
int timer = 1;
int in[MAXN], tour[2 * MAXN];
int depth[MAXN];

struct Sparse
{
    int sparse[2 * MAXN][MAXLOG];
    int lg[2 * MAXN];

    void build(int arr[], int m)
    {
        lg[1] = 0;
        for (int i = 2; i <= m; ++i) lg[i] = lg[i / 2] + 1;

        
        for (int i = 1; i <= m; ++i) sparse[i][0] = arr[i];

        for (int j = 1; (1 << j) <= m; ++j)
        {
            for (int i = 1; i + (1 << j) - 1 <= m; ++i)
            {
                int L = sparse[i][j - 1];
                int R = sparse[i + (1 << (j - 1))][j - 1];
                sparse[i][j] = (depth[L] < depth[R] ? L : R); 
            }
        }
    }

    int query(int l, int r)
    { 
        if (l > r) swap(l, r);
        
        int k = lg[r - l + 1];
        int L = sparse[l][k];
        int R = sparse[r - (1 << k) + 1][k];
        
        return (depth[L] < depth[R] ? L : R);
    }
};


Sparse table;

void build_euler(int node, int par, int currentDepth)
{
    in[node] = timer;
    depth[node] = currentDepth;

    tour[timer++] = node;

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        build_euler(to, node, currentDepth + 1);
        tour[timer++] = node;
    }

}

int lca(int a, int b)
{
    if(in[a] > in[b]) swap(a, b);
    return table.query(in[a], in[b]);
}

void solve()
{
    cin >> n >> q;

    for(int i = 2 ; i <= n ; ++i)
    {
        int parent; cin >> parent;

        tree[parent].push_back(i);
        tree[i].push_back(parent);
    }

    build_euler(1, 0, 0);
    table.build(tour, 2 * n - 1);

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int a, b; cin >> a >> b;
        cout << lca(a, b) << "\n";
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
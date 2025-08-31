#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int MAXLOG = 20;

int n, q;
vector<vector<int>> tree(MAXN);
int in[MAXN], depth[MAXN], tour[2 * MAXN];

struct Sparse
{
    int sparse[2 * MAXN][MAXLOG];
    int lg[2 * MAXN];

    void build(int arr[], int size)
    {
        lg[1] = 0;
        for(int i = 2 ; i <= size ; ++i) lg[i] = lg[i / 2] + 1;

        for(int i = 1 ; i <= size ; ++i) sparse[i][0] = arr[i];

        for(int j = 1 ; (1 << j) <= size ; ++j)
        {
            for(int i = 1 ; i + (1 << j) - 1 <= size ; ++i)
            {
                int L = sparse[i][j - 1];
                int R = sparse[i + (1 << (j - 1))][j - 1];

                sparse[i][j] = (depth[L] < depth[R] ? L : R);
            }
        }
    }

    int query(int l, int r)
    {
        int k = lg[r - l + 1];
        
        int L = sparse[l][k];
        int R = sparse[r - (1 << k) + 1][k];

        return (depth[L] < depth[R] ? L : R);
    }
};

Sparse table;
int timer = 1;

void build_euler(int node, int par, int currentDepth)
{
    in[node] = timer;
    depth[node] = currentDepth;

    tour[timer++] = node;

    for(int& to : tree[node])
    {
        if(to == par) continue;
        
        build_euler(to, node, currentDepth + 1);
        tour[timer++] = node;
    }
}

int distance(int a, int b)
{
    if(in[a] > in[b]) swap(a, b);

    int lca = table.query(in[a], in[b]);
    return depth[a] + depth[b] - 2 * depth[lca];
}

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    build_euler(1, 0, 1);
    table.build(tour, 2 * n - 1);

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int a, b; cin >> a >> b;
        cout << distance(a, b) << "\n";
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
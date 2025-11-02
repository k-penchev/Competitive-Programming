#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int MAXLOG = 17 + 1;

int n, s;
vector<vector<int>> tree(MAXN);
int depth[MAXN], in[MAXN], out[MAXN], timer = 0;
int up[MAXN][MAXLOG];
int A[MAXN], B[MAXN]; // alpha and beta

void dfs1(int node, int par, int currDepth)
{
    in[node] = ++timer;
    depth[node] = currDepth;
    up[node][0] = par;

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prev = up[node][i - 1];
        up[node][i] = up[prev][i - 1];
    }

    for(const int& child : tree[node])
    {
        if(child == par) continue;
        dfs1(child, node, currDepth + 1);
    }

    out[node] = timer;
}

bool is_ancestor(int a, int b)
{
    return (in[a] <= in[b] && out[a] >= out[b]);
}

int lca(int a, int b)
{
    if(is_ancestor(a, b)) return a;
    if(is_ancestor(b, a)) return b;

    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        int nxt = up[a][i];

        if(nxt != 0 && !is_ancestor(nxt, b))
        {
            a = nxt;
        }
    }

    return up[a][0];
}

//f(x) = alpha * depth[x] + beta
//type 0 : alpha = + 1, beta = depth[t] - 2 * depth[LCA]
//type 0 : alpha = - 1, beta = depth[t]
void update(int a, int p, int t, bool type, bool include_top)
{
    int change_a = 0, change_b = 0;

    if(type == 0)
    {
        change_a = +1;
        change_b = depth[t] - 2 * depth[lca(a, t)];
    }
    else
    {
        change_a = -1;
        change_b = depth[t];
    }

    int cut = include_top ? up[p][0] : p;

    A[a] += change_a; A[cut] -= change_a;
    B[a] += change_b; B[cut] -= change_b;
}

void query(int a, int b, int t)
{
    int p = lca(a, b);
    int l1 = lca(a, t);
    int l2 = lca(b, t);

    //case 1
    if(p == t || !is_ancestor(p, t))
    {
        //case 1.1
        if(p == a || p == b) 
        {
            if(p == a) swap(a, b);
            update(a, p, t, 0, true);
        }
        //case 1.2
        else
        {
            update(a, p, t, 0, false);
            update(b, p, t, 0, true);
        }

        return;
    }

    //case 2
    if(p == a || p == b)
    {
        if(p == a)
        {
            swap(a, b);
            swap(l1, l2);
        }

        update(a, l1, t, 0, false);
        update(l1, p, t, 1, true);

        return;
    }

    //case 3
    if(l1 == p && l2 == p)
    {
        update(a, p, t, 0, false);
        update(b, p, t, 0, true);

        return;
    }

    //case 4
    if(depth[l1] < depth[l2])
    {
        swap(a, b);
        swap(l1, l2);
    }

    update(a, l1, t, 0, false);
    update(l1, p, t, 1, false);
    update(b, p, t, 0, true);
}

void dfs2(int node, int par)
{
    for(const int& child : tree[node])
    {
        if(child == par) continue;
        dfs2(child, node);

        A[node] += A[child];
        B[node] += B[child];
    }
}

void solve()
{
    cin >> n >> s;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs1(1, 0, 0);

    for(int i = 1 ; i <= s ; ++i)
    {
        int a, b, t; cin >> a >> b >> t;
        query(a, b, t);
    }

    dfs2(1, 0);

    for(int i = 1 ; i <= n ; ++i)
    {
        cout << A[i] * depth[i] + B[i] << " ";
    }

    cout << "\n";
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
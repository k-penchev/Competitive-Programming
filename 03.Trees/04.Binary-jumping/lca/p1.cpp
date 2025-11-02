#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 50000 + 10;
const int MAXLOG = 17 + 1;

vector<vector<int>> tree(MAXN);

int n, k;
int in[MAXN], out[MAXN], timer = 0;
int cnt[MAXN], lift[MAXN][MAXLOG];

void euler(int node, int par)
{
    in[node] = ++timer;

    lift[node][0] = par;

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prev = lift[node][i - 1];
        lift[node][i] = lift[prev][i - 1];
    }

    for(const int& to : tree[node])
    {
        if(to == par) continue;
        euler(to, node);
    }

    out[node] = timer;
}

bool is_ansector(int a, int b)
{
    return (in[a] <= in[b] && out[a] >= out[b]);
}

int lca(int a, int b)
{
    if (is_ansector(a, b)) return a;
    if (is_ansector(b, a)) return b;

    for (int i = MAXLOG - 1; i >= 0; --i)
    {
        int up = lift[a][i];
        if (up != 0 && !is_ansector(up, b)) a = up;
    }
    
    return lift[a][0];
}

void update(int a, int b)
{
    if(is_ansector(a, b))
    {
        ++cnt[b];

        if(lift[a][0] != 0)
        {
            --cnt[lift[a][0]];
        }

        return;
    }

    if(is_ansector(b, a))
    {
        ++cnt[a];

        if(lift[b][0] != 0)
        {
            --cnt[lift[b][0]];
        }

        return;
    }

    int par = lca(a, b);

    ++cnt[a], ++cnt[b], --cnt[par];

    if(lift[par][0] != 0)
    {
        --cnt[lift[par][0]];
    }
}

void dfs(int node, int par)
{
    for(const int& to : tree[node])
    {
        if(to == par) continue;
        dfs(to, node);
        cnt[node] += cnt[to];
    }
}

void solve()
{
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    cin >> n >> k;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    euler(1, 0);

    for(int i = 1 ; i <= k ; ++i)
    {
        int a, b; cin >> a >> b;
        update(a, b);
    }

    dfs(1, 0);

    cout << *max_element(cnt + 1, cnt + n + 1) << "\n";
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
    
    return 0;
}
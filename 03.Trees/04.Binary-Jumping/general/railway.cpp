#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXLOG = 17 + 1;

int n, m, k;
vector<vector<pair<int, int>>> tree(MAXN);
int parEdge[MAXN]; // idx of the edge (par[x], x)
int lift[MAXN][MAXLOG];
int in[MAXN], out[MAXN], timer = 0;
int dp[MAXN];

void dfs1(int node, int par)
{
    in[node] = ++timer;

    lift[node][0] = par;
    
    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prev = lift[node][i - 1];
        lift[node][i] = lift[prev][i - 1];
    }

    for(const auto& [child,  idx] : tree[node])
    {
        if(child == par) continue;

        parEdge[child] = idx;

        dfs1(child, node);
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
        int up = lift[a][i];

        if(up != 0 && !is_ancestor(up, b))
        {
            a = up;
        }
    }

    return lift[a][0];
}

void update(int a, int b)
{       
    ++dp[a]; ++dp[b];
    dp[lca(a, b)] -= 2;
}

void dfs2(int node, int par)
{
    for(const auto& [child, idx] : tree[node])
    {
        if(child == par) continue;

        dfs2(child, node);

        dp[node] += dp[child];
    }
}

void solve()
{
    cin >> n >> m >> k;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back({b, i});
        tree[b].push_back({a, i});
    }

    dfs1(1, 0);

    for(int i = 1 ; i <= m ; ++i)
    {
        int s;
        
        cin >> s;

        vector<int> cities(s, 0);

        for(int j = 0 ; j < s ; ++j)
        {
            cin >> cities[j];
        }

        sort(cities.begin(), cities.end(), [&](int u, int v)
        {
            return in[u] < in[v];
        });

        for (int j = 0; j < s; ++j)
        {
            int a = cities[j], b = cities[(j + 1) % s];
            update(a, b);
        }
    }

    dfs2(1, 0);

    vector<int> answer;

    for(int i = 2 ; i <= n ; ++i)
    {
        if(dp[i] >= 2 * k)
        {
            answer.push_back(parEdge[i]);
        }
    }

    sort(answer.begin(), answer.end());

    cout << answer.size() << "\n";

    for(int a : answer) cout << a << " ";

    cout << "\n";
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
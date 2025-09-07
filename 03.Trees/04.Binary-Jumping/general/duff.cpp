#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXLOG = 17 + 1;

int n, m, q;
vector<vector<int>> tree(MAXN);
vector<vector<int>> city(MAXN);
int depth[MAXN];
int lift[MAXN][MAXLOG];
vector<int> liftPeople[MAXN][MAXLOG];
int in[MAXN], out[MAXN], timer = 0;

void remove_extra(vector<int>& a)
{
    while(a.size() > 10) a.pop_back();
}

void combine(vector<int>& a, vector<int>& b)
{
    a.insert(a.end(), b.begin(), b.end());
    sort(a.begin(), a.end());
    remove_extra(a);
}

void dfs(int node, int par, int currDepth)
{
    in[node] = ++timer;

    depth[node] = currDepth;
    lift[node][0] = par;
    combine(liftPeople[node][0], city[par]);

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prev = lift[node][i - 1];
        lift[node][i] = lift[prev][i - 1];

        combine(liftPeople[node][i], liftPeople[node][i - 1]);
        combine(liftPeople[node][i], liftPeople[prev][i - 1]);
    }

    for(const int& child : tree[node])
    {
        if(child == par) continue;

        dfs(child, node, currDepth + 1);

    }

    out[node] = timer;
}

bool is_ancestor(int u, int v)
{
    return (in[u] <= in[v] && out[u] >= out[v]);
}

int lca(int u, int v)
{
    if(is_ancestor(u, v)) return u;
    if(is_ancestor(v, u)) return v;

    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        int up = lift[u][i];

        if(up != 0 && !is_ancestor(up, v))
        {
            u = up;
        }
    }

    return lift[u][0];
}

int dist(int u, int v)
{
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

void trace_path(int u, int k, vector<int>& people)
{
    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        if(k & (1 << i))
        {
            combine(people, liftPeople[u][i]);
            u = lift[u][i];
        }
    }
}

void query(int u, int v, int cnt)
{
    vector<int> answer;

    int par = lca(u, v);

    if(par != u) combine(answer, city[u]);
    if(par != v) combine(answer, city[v]);

    int dist1 = dist(u, par);
    int dist2 = dist(v, par);

    trace_path(u, max(0, dist1 - 1), answer);
    trace_path(v, max(0, dist2 - 1), answer);

    combine(answer, city[par]);

    int k = min((int)answer.size(), cnt);

    cout << k << " ";

    for(int i = 0 ; i < k ; ++i)
    {
        cout << answer[i] << " ";
    }

    cout << "\n";
}

void solve()
{
    cin >> n >> m >> q;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int id; cin >> id;
        city[id].push_back(i);
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        sort(city[i].begin(), city[i].end());
        remove_extra(city[i]);
    }

    dfs(1, 0, 0);

    for(int i = 1 ; i <= q ; ++i)
    {
        int a, b, c; cin >> a >> b >> c;
        query(a, b, c);
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
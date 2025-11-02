#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2e5 + 10;
const int MAXLOG = 20 + 1;

int n, l;
vector<vector<pair<int, int>>> tree(MAXN);
int lift[MAXN][MAXLOG], dist[MAXN][MAXLOG], cnt[MAXN];

void dfs1(int node, int par, int currWeight)
{
    lift[node][0] = par;
    dist[node][0] = (par == 0 ? 0 : currWeight);     

    for (int i = 1; i < MAXLOG; ++i)
    {
        int prev = lift[node][i - 1];
        
        if (prev != 0)
        {                          
            lift[node][i] = lift[prev][i - 1];
            dist[node][i] = dist[node][i - 1] + dist[prev][i - 1];
        }
        else
        {
            lift[node][i] = 0;                    
            dist[node][i] = 0;
        }
    }

    for(const auto& [child, w] : tree[node])
    {
        if(child == par) continue;
        dfs1(child, node, w);
    }
}

void dfs2(int node, int par)
{
    for(const auto& [child, w] : tree[node])
    {
        if(child == par) continue;

        dfs2(child, node);

        cnt[node] += cnt[child];
    }
}

void update(int node)
{
    int up = node;
    int rem = l;

    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        if(lift[up][i] != 0 && dist[up][i] <= rem)
        {
            rem -= dist[up][i];
            up = lift[up][i];
        }
    }

    if(lift[up][0] != 0)
    {
        --cnt[lift[up][0]];
    }
}

void solve()
{
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);

    cin >> n >> l;

    for(int i = 2 ; i <= n ; ++i)
    {
        int par, w; cin >> par >> w;
        tree[par].push_back({i, w});
        tree[i].push_back({par, w});
    }

    dfs1(1, 0, 0);

    fill(cnt + 1, cnt + n + 1, 1);

    for(int i = 1 ; i <= n ; ++i)
    {
        update(i);
    }

    dfs2(1, 0);

    for(int i = 1 ; i <= n ; ++i)
    {
        cout << cnt[i] << "\n";
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
    
    return 0;
}
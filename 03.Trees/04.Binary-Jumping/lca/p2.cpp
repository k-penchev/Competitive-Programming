#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int MAXN = 50000 + 10;

int n, k;
vector<pair<int, int>> edge(MAXN);
vector<vector<int>> tree(MAXN);
vector<set<pair<int, int>>> val(MAXN);
int parent[MAXN], ans[MAXN];

void dfs(int node, int par)
{
    parent[node] = par;

    for(const int& child : tree[node])
    {
        if(child == par) continue;

        dfs(child, node);

        if(val[node].size() < val[child].size())
        {
            swap(val[node], val[child]);
        }

        for(pii x : val[child])
        {
            if(val[node].find(x) != val[node].end())
            {
                val[node].erase(x);
            }
            else
            {
                val[node].insert(x);
            }
        }
    }

    ans[node] = (val[node].empty() ? -1 : val[node].begin()->first);
}

void solve()
{
    freopen("disrupt.in", "r", stdin);
    freopen("disrupt.out", "w", stdout);

    cin >> n >> k;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);

        edge[i].first = a, edge[i].second = b;
    }

    for(int i = 1 ; i <= k ; ++i)
    {
        int a, b, w; cin >> a >> b >> w;
        val[a].insert({w, i});
        val[b].insert({w, i});
    }

    dfs(1, 0);

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        //a,b
        int node = (parent[edge[i].first] == edge[i].second ? edge[i].first : edge[i].second);
        cout << ans[node] << "\n";
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
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long

using namespace std;
using namespace __gnu_pbds;

using ordered_set = tree <int, null_type, less<int> , rb_tree_tag, tree_order_statistics_node_update>; 

const int MAXN = 1e5 + 10;

int n;
vector<vector<int>> g(MAXN);
ordered_set s[MAXN];
int p[MAXN];
int ans[MAXN];


void dfs(int node, int par)
{
    for(const int& child : g[node])
    {
        if(child == par) continue;

        dfs(child, node);

        if(s[node].size() < s[child].size()) s[node].swap(s[child]);

        for(int val : s[child])
        {
            s[node].insert(val);
        }
    }

    ans[node] = s[node].size() - s[node].order_of_key(p[node]);
    s[node].insert(p[node]);
}

void solve()
{
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);

    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        int x; cin >> x;
        p[i] = x;
    }

    for(int i = 2 ; i <= n ; ++i)
    {
        int par; cin >> par;
        g[par].push_back(i);
        g[i].push_back(par);
    }

    dfs(1, 0);

    for(int i = 1 ; i <= n ; ++i) cout << ans[i] << "\n";
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
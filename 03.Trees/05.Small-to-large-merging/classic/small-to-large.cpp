#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
set<int> s[MAXN];
int ans[MAXN];

void dfs(int node, int par)
{
    for(const int& child : tree[node])
    {
        if(child == par) continue;

        dfs(child, node);

        //s[child] -> s[node]

        if(s[node].size() < s[child].size()) swap(s[node], s[child]);

        for(int c : s[child]) s[node].insert(c);
    }

    ans[node] = s[node].size();
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        int x; cin >> x;
        s[i].insert(x);
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0);

    for(int i = 1 ; i <= n ; ++i) cout << ans[i] << " ";
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
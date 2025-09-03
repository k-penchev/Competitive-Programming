#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

int n;
vector<vector<int>> tree(MAXN);

void dfs(int node, int par)
{
    cout << "\n";
    cout << "Entering " << node << "\n";

    for(int to : tree[node])
    {
        if(to == par) continue;

        cout << "Entering child " << to << " from " << node << "\n";

        dfs(to, node);

        cout << "Exiting child " << to << " from " << node << "\n";
    }

    cout << "Exiting " << node << "\n";
    cout << "\n";
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    dfs(1, 0);
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
}
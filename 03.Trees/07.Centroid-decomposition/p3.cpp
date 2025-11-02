#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
long long siz[MAXN];
long long cnt = 0;
vector<int> tour, ans;

void findSize(int node, int par)
{
    siz[node] = 1;

    for(const int& child : tree[node])
    {
        if(child == par) continue;

        findSize(child, node);
        siz[node] += siz[child];
    }
}

void dfs(int node, int par)
{
    cnt += 2 * min(siz[node], n - siz[node]);
    tour.push_back(node);

    for(const int& child : tree[node])
    {
        if(child == par) continue;

        dfs(child, node);
    }
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b; --a, --b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    ans.resize(n, 0);

    findSize(0, -1);
    dfs(0, -1);

    for(int i = 0 ; i < n ; ++i)
    {
        int shifted = (i + n / 2) % n;
        ans[tour[shifted]] = tour[i];
    }

    cout << cnt << "\n";

    for(int i = 0 ; i < n ; ++i)
    {
        cout << ans[i] + 1 << " ";
    }

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
}
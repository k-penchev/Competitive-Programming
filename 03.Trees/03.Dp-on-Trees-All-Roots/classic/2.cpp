#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
int best1[MAXN], best2[MAXN];

void dfs(int node, int par)
{
    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs(to, node);

        int candidate = 1 + best1[to];

        if(candidate > best1[node])
        {
            best2[node] = best1[node];
            best1[node] = candidate;
        }
        else if(candidate > best2[node])
        {
            best2[node] = candidate;
        }
    }
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

    int diameter = 0;

    for(int i = 1 ; i <= n ; ++i)
    {
        diameter = max(diameter, best1[i] + best2[i]);
    }

    cout << diameter << "\n";
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
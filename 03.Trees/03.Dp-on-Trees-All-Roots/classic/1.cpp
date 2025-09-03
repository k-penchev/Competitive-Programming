#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
long long down[MAXN], up[MAXN];
long long best1[MAXN], best2[MAXN], through[MAXN];
long long ans[MAXN];

void dfs2(int node, int par)
{
    for(int& child : tree[node])
    {
        if(child == par) continue;

        long long other = (child == through[node] ? best2[node] : best1[node]);

        up[child] = 1 + max(up[node], other);

        dfs2(child, node);
    }
}

void dfs1(int node, int par)
{
    for(int& child : tree[node])
    {
        if(child == par) continue;

        dfs1(child, node);

        int candidate = 1 + down[child];

        if(candidate > best1[node])
        {
            best2[node] = best1[node];
            best1[node] = candidate;
            through[node] = child;
        }
        else if(candidate > best2[node])
        {
            best2[node] = candidate;
        }
    }

    down[node] = best1[node];
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

    dfs1(1, 0);
    dfs2(1, 0);

    for(int i = 1 ; i <= n ; ++i)
    {
        ans[i] = max(down[i], up[i]);
        cout << ans[i] << " ";
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
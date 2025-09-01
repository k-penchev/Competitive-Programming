#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n, q;
vector<vector<int>> tree(MAXN);
int in[MAXN], out[MAXN], timer = 0;
vector<vector<int>> depth(MAXN);

int binary(vector<int>& v, int k)
{
    int l = -1, r = v.size();

    while(r > l + 1)
    {
        int m = (l + r) / 2;

        if(v[m] >= k) r = m;
        else l = m;
    }

    return r;
}

void euler(int node, int par, int currentDepth)
{
    in[node] = ++timer;

    depth[currentDepth].push_back(in[node]);

    for(int& to : tree[node])
    {
        if(to == par) continue;
        euler(to, node, currentDepth + 1);
    }

    out[node] = timer;
}

void solve()
{
    cin >> n;

    for(int i = 2 ; i <= n ; ++i)
    {
        int parent; cin >> parent;

        tree[parent].push_back(i);
        tree[i].push_back(parent);
    }

    euler(1, 0, 0);

    cin >> q;

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int u, d; cin >> u >> d;
        
        int high = binary(depth[d], out[u] + 1);
        int low = binary(depth[d], in[u]);
        
        cout << high - low << "\n";
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
}
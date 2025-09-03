#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 10;
const int LOG = 20;

int n, q;
vector<pair<int,int>> g[MAXN];
int up[MAXN][LOG + 1], depth[MAXN];
long long distRoot[MAXN];

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i <= LOG; ++i)
        up[u][i] = up[ up[u][i - 1] ][i - 1];

    for (auto [v, w] : g[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        distRoot[v] = distRoot[u] + (long long) w;
        dfs(v, u);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];
    for (int i = LOG; i >= 0; --i)
        if (k & (1 << i)) a = up[a][i];

    if (a == b) return a;

    for (int i = LOG; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

long long distBetween(int a, int b) {
    int c = lca(a, b);
    return distRoot[a] + distRoot[b] - 2LL * distRoot[c];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, w; cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }

    depth[1] = 0;
    distRoot[1] = 0;
    
    dfs(1, 0);

    while (q--) {
        int a, b; cin >> a >> b;
        cout << distBetween(a, b) << "\n";
    }
}

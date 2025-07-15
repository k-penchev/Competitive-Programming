#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 17;

vector<pair<int, int>> adj[MAXN];  // {neighbor, edge_index}
int subtree_size[MAXN], depth[MAXN], parent[MAXN][LOG];
int heavy[MAXN], head[MAXN], pos[MAXN], value[MAXN];
int segtree[4 * MAXN], lazy[4 * MAXN];
int edge_weights[MAXN], edge_index[MAXN];
int timer = 0, n;

// DFS to calculate subtree sizes and find heavy child
void dfs(int u, int p, int d) {
    parent[u][0] = p;
    depth[u] = d;
    subtree_size[u] = 1;
    heavy[u] = -1;

    int max_subtree = 0;
    for (auto [v, idx] : adj[u]) {
        if (v == p) continue;
        edge_index[v] = idx;  // Store the edge index
        dfs(v, u, d + 1);
        subtree_size[u] += subtree_size[v];
        if (subtree_size[v] > max_subtree) {
            max_subtree = subtree_size[v];
            heavy[u] = v;
        }
    }
}

// Decomposes the tree into heavy-light chains
void decompose(int u, int h) {
    head[u] = h;
    pos[u] = timer++;
    value[pos[u]] = edge_weights[edge_index[u]];

    if (heavy[u] != -1) {
        decompose(heavy[u], h);
    }

    for (auto [v, idx] : adj[u]) {
        if (v != parent[u][0] && v != heavy[u]) {
            decompose(v, v);
        }
    }
}

// Builds the segment tree
void build(int node, int l, int r) {
    if (l == r) {
        segtree[node] = value[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

// Updates a single position in the segment tree
void update(int node, int l, int r, int pos, int new_val) {
    if (l == r) {
        segtree[node] = new_val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(node * 2, l, mid, pos, new_val);
    else update(node * 2 + 1, mid + 1, r, pos, new_val);
    segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}

// Queries the segment tree for sum
int query(int node, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (l == ql && r == qr) return segtree[node];
    int mid = (l + r) / 2;
    return query(node * 2, l, mid, ql, min(qr, mid)) +
           query(node * 2 + 1, mid + 1, r, max(ql, mid + 1), qr);
}

// LCA preprocessing using binary lifting
void preprocess_lca(int n) {
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (parent[i][j - 1] != -1)
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }
}

// Finds LCA using binary lifting
int find_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int j = LOG - 1; j >= 0; j--) {
        if (depth[u] - (1 << j) >= depth[v])
            u = parent[u][j];
    }
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }
    return parent[u][0];
}

// Queries sum in the path u to v using HLD
int path_query(int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        res += query(1, 0, n - 1, pos[head[u]], pos[u]);
        u = parent[head[u]][0];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res += query(1, 0, n - 1, pos[u] + 1, pos[v]);  // Exclude LCA
    return res;
}

// Updates edge weight
void update_edge(int u, int new_val) {
    update(1, 0, n - 1, pos[u], new_val);
}

// Main function
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        edge_weights[i] = w;
    }

    memset(parent, -1, sizeof(parent));

    // Step 1: DFS for subtree sizes
    dfs(1, -1, 0);

    // Step 2: Decomposition
    decompose(1, 1);

    // Step 3: Build segment tree
    build(1, 0, n - 1);

    // Step 4: Preprocess LCA
    preprocess_lca(n);

    int q;
    cin >> q;
    while (q--) {
        string type;
        cin >> type;
        if (type == "QUERY") {
            int a, b;
            cin >> a >> b;
            int lca = find_lca(a, b);
            cout << path_query(a, lca) + path_query(b, lca) << "\n";
        } else if (type == "UPDATE") {
            int edge, new_val;
            cin >> edge >> new_val;
            update_edge(edge, new_val);
        }
    }

    return 0;
}

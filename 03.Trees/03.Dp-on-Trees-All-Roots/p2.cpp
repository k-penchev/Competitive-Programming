#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;

int N, M;
vector<vector<int>> tree(MAXN);

// dp[u]  = product over children v of (dp[v] + 1)  (subtree-only, rooted at 1)
// up[u]  = parent/siblings contribution for u, seen from the parent side
// ans[u] = final rerooted answer at u = (up[u] + 1) * product over children (dp[v] + 1)
int dp[MAXN], upv[MAXN], ans[MAXN];   // FIX: added upv[]; ans[] will store final answers

/*--------------------- dfs1: compute subtree dp ---------------------

   FIX: The correct formula for this problem is:
        dp[u] = Π (dp[v] + 1) over children v
        (NOT 1 + Π dp[v], and no special "leaf = 2")

--------------------------------------------------------------------*/
void dfs1(int u, int p) {
    int prod = 1 % M;
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs1(v, u);
        // multiply by (dp[v] + 1), modulo M
        prod = (prod * ((dp[v] + 1) % M)) % M;  // FIX: dp[v] + 1 instead of dp[v]
    }
    dp[u] = prod;                               // FIX: leaf implicitly gets 1 (empty product)
}

/*--------------------- dfs2: reroot with prefix/suffix ---------------------

   FIX: No modular division! We build prefix/suffix products of (dp[child]+1).
        The contribution sent from u to a child v is:
           up[v] = (up[u] + 1) * Π_{w != v} (dp[w] + 1)   (all modulo M)
        Then the final answer at u is:
           ans[u] = (up[u] + 1) * Π_{children w} (dp[w] + 1)

--------------------------------------------------------------------------*/
void dfs2(int u, int p) {
    // Build a compact list of children (exclude parent)
    vector<int> ch;
    ch.reserve(tree[u].size());
    for (int v : tree[u]) if (v != p) ch.push_back(v);

    // Prefix/suffix products of (dp[child] + 1)
    int k = (int)ch.size();
    vector<int> pref(k + 1, 1), suf(k + 1, 1);   // FIX: prefix/suffix instead of division

    for (int i = 0; i < k; ++i) {
        int v = ch[i];
        pref[i + 1] = (pref[i] * ((dp[v] + 1) % M)) % M;
    }
    for (int i = k - 1; i >= 0; --i) {
        int v = ch[i];
        suf[i] = (suf[i + 1] * ((dp[v] + 1) % M)) % M;
    }

    // Final answer for u: combine parent-side and all children
    ans[u] = ( ((upv[u] + 1) % M) * (pref[k] % M) ) % M;  // FIX: (up[u]+1) * Π children (dp+1)

    // Push contributions to children
    for (int i = 0; i < k; ++i) {
        int v = ch[i];
        // Excluding v: pref[i] * suf[i+1]
        int siblings = (pref[i] * suf[i + 1]) % M;
        // up[v] = (up[u] + 1) * siblings
        upv[v] = ( ((upv[u] + 1) % M) * siblings ) % M;   // FIX: compute child’s up without division
        dfs2(v, u);
    }
}

void solve() {
    cin >> N >> M;

    for (int i = 1; i <= N - 1; ++i) {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // Root the tree at 1
    dfs1(1, 0);

    // Root has no parent-side contribution
    upv[1] = 0;                // FIX: up[root] = 0
    dfs2(1, 0);

    // For EDPC V, we print ans[u] as-is (no "-1" subtraction).
    // FIX: Do NOT subtract 1; the connected set containing u is never empty.
    for (int i = 1; i <= N; ++i) {
        cout << ans[i] % M << (i == N ? '\n' : ' ');
    }
}

void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

signed main() {
    fastIO();
    solve();
}

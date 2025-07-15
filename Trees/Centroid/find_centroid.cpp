#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl '\n'

const ll mxN = 2 * 1e5 + 5;

ll n;
vector<vector<ll>> tree(mxN);
ll sub_sz[mxN];

void dfs(ll node, ll par) {
    sub_sz[node] = 1;
    
    for (ll child : tree[node]) {
        if (child == par) continue;
        dfs(child, node);  // Fix: Recursively calculate subtree sizes
        sub_sz[node] += sub_sz[child];
    }
}

ll find_centroid(ll node, ll par) {
    for (ll child : tree[node]) {
        if (child == par) continue;

        
        if (sub_sz[child] > n / 2) {
            return find_centroid(child, node); 
        }
    }
    
    return node;  
}

void solve() {
    cin >> n;

    for (ll i = 0; i < n - 1; i++) {
        ll a, b;
        cin >> a >> b;
        --a, --b;  
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(0, -1); 

    cout << find_centroid(0, -1) + 1 << endl;  
}

void speed() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

int main() {
    speed();
    solve();
    return 0;
}

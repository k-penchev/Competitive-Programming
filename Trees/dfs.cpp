#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
vector<int> tree[MAXN];

void dfs(int node, int parent) {

    for (int neighbor : tree[node]) {
        if (neighbor != parent) {
            dfs(neighbor, node);
        }
    }
}

int main() {
    int n;
    cin >> n; 
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    return 0;
}

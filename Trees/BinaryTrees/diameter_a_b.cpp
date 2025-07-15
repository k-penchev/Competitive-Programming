#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
vector<int> tree[MAXN];
int farthestNode, maxDistance;

void dfs(int node, int parent, int distance) {
    if (distance > maxDistance) {
        maxDistance = distance;
        farthestNode = node;
    }

    for (int neighbor : tree[node]) {
        if (neighbor != parent) {
            dfs(neighbor, node, distance + 1);
        }
    }
}

int main() {
    int n;
    cin >> n; // Number of nodes
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    maxDistance = 0;
    dfs(1, -1, 0); // First DFS to find the farthest node from any node (assuming 1 as the root)

    maxDistance = 0;
    dfs(farthestNode, -1, 0); // Second DFS from the farthest node to find the diameter

    cout << "Diameter of the tree (without DP): " << maxDistance << endl;

    return 0;
}

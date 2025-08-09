#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to perform DFS and calculate the max path length for each node
void dfs(int node, int parent, const vector<vector<int>>& adj, vector<int>& maxPath) {
    int maxLength = 0; // Tracks the maximum path length from the current node
    for (int neighbor : adj[node]) {
        if (neighbor != parent) { // Ensure we don't revisit the parent
            dfs(neighbor, node, adj, maxPath);
            maxLength = max(maxLength, 1 + maxPath[neighbor]);
        }
    }
    maxPath[node] = maxLength; // Store the maximum path length for the current node
}

int main() {
    int n; // Number of nodes in the tree
    cin >> n;

    vector<vector<int>> adj(n); // Adjacency list representation of the tree
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v; // Convert to zero-based indexing
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> maxPath(n, 0); // To store the max path length for each node

    // Perform DFS starting from the root (node 0)
    dfs(0, -1, adj, maxPath);

    // Output the max path lengths for all nodes
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i + 1 << ": " << maxPath[i] << endl;
    }

    return 0;
}

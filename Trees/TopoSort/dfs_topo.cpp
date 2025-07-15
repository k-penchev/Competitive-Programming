#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int node, vector<bool>& visited, stack<int>& topoStack, vector<vector<int>>& adj) {
    visited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, visited, topoStack, adj);
        }
    }

    topoStack.push(node);
}

void topologicalSortDFS(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    stack<int> topoStack;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, visited, topoStack, adj);
        }
    }

    cout << "Topological Sort (DFS): ";
    while (!topoStack.empty()) {
        cout << topoStack.top() << " ";
        topoStack.pop();
    }
    cout << endl;
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n);
    cout << "Enter edges (u -> v):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    topologicalSortDFS(n, adj);
    return 0;
}

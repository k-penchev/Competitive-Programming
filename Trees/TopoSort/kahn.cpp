#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void topologicalSortKahn(int n, vector<vector<int>>& adj) {
    vector<int> inDegree(n, 0);

    // Calculate in-degrees of all vertices
    for (int i = 0; i < n; i++) {
        for (int neighbor : adj[i]) {
            inDegree[neighbor]++;
        }
    }

    queue<int> q;

    // Add all vertices with in-degree 0 to the queue
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topoOrder;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);

        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (topoOrder.size() == n) {
        cout << "Topological Sort (Kahn's Algorithm): ";
        for (int node : topoOrder) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "The graph has a cycle, topological sort not possible!" << endl;
    }
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

    topologicalSortKahn(n, adj);
    return 0;
}

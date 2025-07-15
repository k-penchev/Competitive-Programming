#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int v, weight;
};

void prim(int n, vector<vector<Edge>>& adj) {
    vector<bool> inMST(n, false);
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);

    key[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto edge : adj[u]) {
            int v = edge.v;
            int weight = edge.weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    int mstWeight = 0;
    cout << "Edges in MST:" << endl;
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " : " << key[i] << endl;
            mstWeight += key[i];
        }
    }

    cout << "MST Weight (Prim): " << mstWeight << endl;
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<Edge>> adj(n);
    cout << "Enter edges (u v weight):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    prim(n, adj);
    return 0;
}

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void bellmanFord(int V, int E, vector<tuple<int, int, int>> &edges, int S) {
    vector<int> distance(V, INT_MAX);
    distance[S] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; ++i) {
        for (auto &[u, v, w] : edges) {
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }

    // Check for negative weight cycles
    for (auto &[u, v, w] : edges) {
        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            cout << "-1\n";
            return;
        }
    }

    // Print distances
    for (int i = 0; i < V; ++i) {
        if (distance[i] == INT_MAX) {
            cout << "INF ";
        } else {
            cout << distance[i] << " ";
        }
    }
    cout << "\n";
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int V, E;
        cin >> V >> E;

        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < E; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            edges.emplace_back(u, v, w);
        }

        int S;
        cin >> S;

        bellmanFord(V, E, edges, S);
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> Edge; // Pair to represent (distance, vertex)

void dijkstra(int source, const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; 

    dist[source] = 0;
    pq.push({0, source}); // Push the source with distance 0

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // Skip if the distance is outdated
        if (currentDist > dist[currentNode]) continue;

        // Traverse all neighbors
        for (const auto& neighbor : graph[currentNode]) {
            int neighborNode = neighbor.second;
            int weight = neighbor.first;

            if (dist[currentNode] + weight < dist[neighborNode]) {
                dist[neighborNode] = dist[currentNode] + weight;
                pq.push({dist[neighborNode], neighborNode});
            }
        }
    }

    // Print shortest distances
    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < n; ++i) {
        cout << i << "\t" << (dist[i] == numeric_limits<int>::max() ? -1 : dist[i]) << "\n";
    }
}

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices and edges: ";
    cin >> vertices >> edges;

    vector<vector<Edge>> graph(vertices);

    cout << "Enter edges in the format (u v w), where u and v are vertices and w is the weight:\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({w, v});
        graph[v].push_back({w, u}); // For undirected graph; remove for directed
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    dijkstra(source, graph);

    return 0;
}

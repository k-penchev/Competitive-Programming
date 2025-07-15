#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int find(int u, vector<int>& parent) {
    if (parent[u] != u)
        parent[u] = find(parent[u], parent);
    return parent[u];
}

void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = find(u, parent);
    int rootV = find(v, parent);
    if (rootU != rootV) {
        if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

void kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n);
    vector<int> rank(n, 0);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    vector<Edge> mst;
    int mstWeight = 0;

    for (auto edge : edges) {
        if (find(edge.u, parent) != find(edge.v, parent)) {
            mst.push_back(edge);
            mstWeight += edge.weight;
            unionSets(edge.u, edge.v, parent, rank);
        }
    }

    cout << "MST Weight (Kruskal): " << mstWeight << endl;
    cout << "Edges in MST:" << endl;
    for (auto edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Enter edges (u v weight):" << endl;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    kruskal(n, edges);
    return 0;
}

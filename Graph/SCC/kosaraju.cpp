// Kosaraju.cpp - Kosaraju's Algorithm
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs1(int node, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &finishStack) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs1(neighbor, adj, visited, finishStack);
        }
    }
    finishStack.push(node);
}

void dfs2(int node, vector<vector<int>> &reverseAdj, vector<bool> &visited, vector<int> &component) {
    visited[node] = true;
    component.push_back(node);
    for (int neighbor : reverseAdj[node]) {
        if (!visited[neighbor]) {
            dfs2(neighbor, reverseAdj, visited, component);
        }
    }
}

void kosaraju(int V, vector<vector<int>> &adj) {
    vector<vector<int>> reverseAdj(V);
    for (int i = 0; i < V; i++) {
        for (int neighbor : adj[i]) {
            reverseAdj[neighbor].push_back(i);
        }
    }

    vector<bool> visited(V, false);
    stack<int> finishStack;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs1(i, adj, visited, finishStack);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!finishStack.empty()) {
        int node = finishStack.top();
        finishStack.pop();
        if (!visited[node]) {
            vector<int> component;
            dfs2(node, reverseAdj, visited, component);
            cout << "SCC: ";
            for (int v : component) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int V = 5;
    vector<vector<int>> adj = {
        {1}, {2}, {0, 3}, {4}, {}
    };

    kosaraju(V, adj);
    return 0;
}

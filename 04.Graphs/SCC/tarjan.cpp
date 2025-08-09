// Tarjan.cpp - Tarjan's Algorithm
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void tarjanDFS(int node, vector<vector<int>> &adj, vector<int> &disc, vector<int> &low, stack<int> &st, vector<bool> &inStack, int &time, vector<vector<int>> &sccs) {
    disc[node] = low[node] = time++;
    st.push(node);
    inStack[node] = true;

    for (int neighbor : adj[node]) {
        if (disc[neighbor] == -1) {
            tarjanDFS(neighbor, adj, disc, low, st, inStack, time, sccs);
            low[node] = min(low[node], low[neighbor]);
        } else if (inStack[neighbor]) {
            low[node] = min(low[node], disc[neighbor]);
        }
    }

    if (low[node] == disc[node]) {
        vector<int> component;
        int w;
        do {
            w = st.top();
            st.pop();
            inStack[w] = false;
            component.push_back(w);
        } while (w != node);
        sccs.push_back(component);
    }
}

void tarjan(int V, vector<vector<int>> &adj) {
    vector<int> disc(V, -1), low(V, -1);
    vector<bool> inStack(V, false);
    stack<int> st;
    vector<vector<int>> sccs;
    int time = 0;

    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            tarjanDFS(i, adj, disc, low, st, inStack, time, sccs);
        }
    }

    for (const auto &component : sccs) {
        cout << "SCC: ";
        for (int v : component) {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
    int V = 5;
    vector<vector<int>> adj = {
        {1}, {2}, {0, 3}, {4}, {}
    };

    tarjan(V, adj);
    return 0;
}

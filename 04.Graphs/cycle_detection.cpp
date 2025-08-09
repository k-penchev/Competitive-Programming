#include <iostream>
#include <vector>

const int MAX_NODES = 100;
int graph[MAX_NODES][MAX_NODES]; // Adjacency matrix for the graph
bool visited[MAX_NODES];
bool recursionStack[MAX_NODES];

bool hasCycle(int node, int numNodes) {
    visited[node] = true;
    recursionStack[node] = true;

    for (int neighbor = 0; neighbor < numNodes; ++neighbor) {
        if (graph[node][neighbor]) { // Check if there's an edge
            if (!visited[neighbor] && hasCycle(neighbor, numNodes))
                return true;
            else if (recursionStack[neighbor])
                return true;
        }
    }

    recursionStack[node] = false;
    return false;
}

int main() {
    int numNodes, numEdges;
    std::cout << "Enter number of nodes and edges: ";
    std::cin >> numNodes >> numEdges;

    // Initialize the graph and visited arrays
    for (int i = 0; i < numNodes; ++i) {
        visited[i] = false;
        recursionStack[i] = false;
        for (int j = 0; j < numNodes; ++j) {
            graph[i][j] = 0;
        }
    }

    // Input the edges
    std::cout << "Enter the edges (from to):" << std::endl;
    for (int i = 0; i < numEdges; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph[from][to] = 1;
    }

    // Check for cycle
    bool cycleFound = false;
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i] && hasCycle(i, numNodes)) {
            cycleFound = true;
            break;
        }
    }

    if (cycleFound)
        std::cout << "Graph contains a cycle" << std::endl;
    else
        std::cout << "Graph does not contain a cycle" << std::endl;

    return 0;
}

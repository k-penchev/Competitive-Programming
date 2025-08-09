#include <vector>
#include <queue>
using namespace std;

bool isBipartite(vector<vector<int>>& adj, int n) {
    vector<int> color(n, -1); // -1: not colored, 0: first color, 1: second color

    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) { // Unvisited node
            queue<int> q;
            q.push(i);
            color[i] = 0;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) {
                        // Assign opposite color to the neighbor
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) {
                        // Same color as the current node => Not bipartite
                        return false;
                    }
                }
            }
        }
    }
    return true; 
}

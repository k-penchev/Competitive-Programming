#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
vector<int> tree[MAXN];
int dp[MAXN]; // dp[node] stores the maximum height of the subtree rooted at `node`
int global_diameter = 0; // To store the diameter of the tree

void dfs(int node, int parent) {
    cout << "Entering DFS for node " << node << " (parent: " << parent << ")" << endl;

    vector<int> heights; // To store the heights of child subtrees for the current node

    // Explore all neighbors of the current node
    for (int neighbor : tree[node]) {
        if (neighbor != parent) { // Avoid revisiting the parent node
            dfs(neighbor, node); // Recursive DFS call for child node
            heights.push_back(dp[neighbor] + 1); // Store the height of this child's subtree
            cout << "Height of subtree rooted at child " << neighbor << " is " << dp[neighbor] + 1 << endl;
        }
    }

    // Sort the heights in descending order to get the two largest heights
    sort(heights.rbegin(), heights.rend());

    // Calculate the diameter through the current node if there are at least two child subtrees
    if (heights.size() >= 2) {
        int current_diameter = heights[0] + heights[1];
        cout << "Node " << node << ": Two largest heights are " << heights[0] << " and " << heights[1] << endl;
        cout << "Node " << node << ": Diameter through this node is " << current_diameter << endl;

        // Update the global diameter if this one is larger
        global_diameter = max(global_diameter, current_diameter);
        cout << "Global diameter updated to " << global_diameter << endl;
    }

    // Update dp[node] with the largest height from its children (or 0 if no children exist)
    if (!heights.empty()) {
        dp[node] = heights[0];
    } else {
        dp[node] = 0; // Leaf node
    }

    cout << "Exiting DFS for node " << node << " with dp[" << node << "] = " << dp[node] << endl;
}

int main() {
    int n;
   // cout << "Enter the number of nodes: ";
    cin >> n;

    //cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    cout << "\nStarting DFS from node 1...\n" << endl;
    dfs(1, -1); // Assuming node 1 is the root

    // for(int i = 1; i <= n; i++){
    //     cout << "dp[" << i << "] =" << dp[i] << endl;
    // }

    cout << "\nFinal Diameter of the Tree: " << global_diameter << endl;
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

// Adjacency list representation of the binary tree
vector<vector<int>> adj;

// Recursive pre-order traversal
void preOrder(int node) {
    if (node == -1) return; // If the node is empty
    
    cout << node << " ";               // Process the root
    if (!adj[node].empty()) {
        preOrder(adj[node][0]);        // Traverse the left subtree
        if (adj[node].size() > 1) {
            preOrder(adj[node][1]);    // Traverse the right subtree
        }
    }
}

// Recursive in-order traversal
void inOrder(int node) {
    if (node == -1) return; // If the node is empty

    if (!adj[node].empty()) {
        inOrder(adj[node][0]);         // Traverse the left subtree
    }
    cout << node << " ";               // Process the root
    if (!adj[node].empty() && adj[node].size() > 1) {
        inOrder(adj[node][1]);         // Traverse the right subtree
    }
}

// Recursive post-order traversal
void postOrder(int node) {
    if (node == -1) return; // If the node is empty

    if (!adj[node].empty()) {
        postOrder(adj[node][0]);       // Traverse the left subtree
        if (adj[node].size() > 1) {
            postOrder(adj[node][1]);  // Traverse the right subtree
        }
    }
    cout << node << " ";               // Process the root
}

int main() {
    // Number of nodes in the binary tree
    int n = 7;

    // Resize the adjacency list
    adj.resize(n + 1);

    // Constructing the binary tree
    // For the example tree:
    //     1
    //    / \
    //   2   3
    //  / \    \
    // 4   5    6
    //            \
    //             7
    adj[1] = {2, 3}; // Node 1 has children 2 and 3
    adj[2] = {4, 5}; // Node 2 has children 4 and 5
    adj[3] = {-1, 6}; // Node 3 has no left child (-1) and right child 6
    adj[4] = {};      // Node 4 is a leaf
    adj[5] = {};      // Node 5 is a leaf
    adj[6] = {-1, 7}; // Node 6 has no left child (-1) and right child 7
    adj[7] = {};      // Node 7 is a leaf

    cout << "Pre-order traversal: ";
    preOrder(1);
    cout << endl;

    cout << "In-order traversal: ";
    inOrder(1);
    cout << endl;

    cout << "Post-order traversal: ";
    postOrder(1);
    cout << endl;

    return 0;
}

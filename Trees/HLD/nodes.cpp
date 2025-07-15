#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 200005;  // maximum number of nodes
const int LOG_MAX = 20;        // enough for n up to ~2e5

// Global variables (zero‐based indexing)
int numNodes, numQueries;
int nodeValue[MAX_NODES];            // value for each node, nodes 0..numNodes-1
vector<int> graph[MAX_NODES];        // tree as an adjacency list

// For DFS and Heavy–Light Decomposition:
int subtreeSize[MAX_NODES];          // size of subtree rooted at each node
int parentNode[MAX_NODES];           // immediate parent of each node (-1 for root)
int depth[MAX_NODES];                // depth (distance from the root)
int positionInBase[MAX_NODES];       // position of node in the base array (for segtree)
int chainTop[MAX_NODES];             // top (head) of the heavy–light chain for each node
int currPos = 0;                     // current position counter (starts at 0)

// For Binary Lifting (LCA):
int jump[MAX_NODES][LOG_MAX];        // jump[u][d] is the 2^d–th ancestor of node u

// Recursive Segment Tree arrays and functions:
// We allocate an array of size 4 * numNodes for the recursive segment tree.
int segTreeRec[4 * MAX_NODES];

/// Recursive function to build the segment tree.
/// - idx: current index in segTreeRec.
/// - l, r: range of the base array that this node covers.
/// - baseArray: the vector storing node values in heavy–light order.
void buildSegmentTreeRec(int idx, int l, int r, const vector<int>& baseArray) {
    if(l == r) {
        segTreeRec[idx] = baseArray[l];
        cout << "[SegTree Rec] Build leaf idx " << idx << " covering [" << l << "] set to " << baseArray[l] << "\n";
        return;
    }
    int mid = (l + r) / 2;
    buildSegmentTreeRec(2 * idx, l, mid, baseArray);
    buildSegmentTreeRec(2 * idx + 1, mid + 1, r, baseArray);
    segTreeRec[idx] = max(segTreeRec[2 * idx], segTreeRec[2 * idx + 1]);
    cout << "[SegTree Rec] Build internal idx " << idx << " covering [" << l << ", " << r << "] set to " << segTreeRec[idx] << "\n";
}

/// Recursive function to update the segment tree.
/// - idx: current index in segTreeRec.
/// - l, r: range of the base array that this node covers.
/// - pos: position in baseArray to update.
/// - newValue: new value to be set at position pos.
void updateSegmentTreeRec(int idx, int l, int r, int pos, int newValue) {
    if(l == r) {
        segTreeRec[idx] = newValue;
        cout << "[SegTree Rec] Update leaf idx " << idx << " covering [" << l << "] set to " << newValue << "\n";
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid)
        updateSegmentTreeRec(2 * idx, l, mid, pos, newValue);
    else
        updateSegmentTreeRec(2 * idx + 1, mid + 1, r, pos, newValue);
    segTreeRec[idx] = max(segTreeRec[2 * idx], segTreeRec[2 * idx + 1]);
    cout << "[SegTree Rec] Update internal idx " << idx << " covering [" << l << ", " << r << "] updated to " << segTreeRec[idx] << "\n";
}

/// Recursive function to query the segment tree for the maximum value in [ql, qr].
/// - idx: current index in segTreeRec.
/// - l, r: range of the base array that this node covers.
/// - ql, qr: query range.
int querySegmentTreeRec(int idx, int l, int r, int ql, int qr) {
    if(ql > r || qr < l) {
        // No overlap.
        return 0;
    }
    if(ql <= l && r <= qr) {
        cout << "[SegTree Rec] Query idx " << idx << " covering [" << l << ", " << r << "] fully in range, returning " << segTreeRec[idx] << "\n";
        return segTreeRec[idx];
    }
    int mid = (l + r) / 2;
    int leftQuery = querySegmentTreeRec(2 * idx, l, mid, ql, min(qr, mid));
    int rightQuery = querySegmentTreeRec(2 * idx + 1, mid + 1, r, max(ql, mid + 1), qr);
    int result = max(leftQuery, rightQuery);
    cout << "[SegTree Rec] Query idx " << idx << " covering [" << l << ", " << r << "] returns " << result << "\n";
    return result;
}

//-------------------------
// Function: computeSubtreeSizes
// A DFS that computes the subtree sizes, parent for each node, and each node’s depth.
void computeSubtreeSizes(int current, int parent) {
    cout << "[DFS] Entering computeSubtreeSizes for node " << current 
         << " with parent " << parent << "\n";
    parentNode[current] = parent;
    subtreeSize[current] = 1;
    for (int child : graph[current]) {
        if (child == parent) continue;
        depth[child] = depth[current] + 1;
        computeSubtreeSizes(child, current);
        subtreeSize[current] += subtreeSize[child];
    }
    cout << "[DFS] Leaving node " << current << " with subtreeSize " 
         << subtreeSize[current] << "\n";
}

//-------------------------
// Function: initializeLCA
// Sets up the binary lifting (jump) table using parentNode array.
void initializeLCA() {
    cout << "[LCA] Initializing LCA jump table...\n";
    for (int i = 0; i < numNodes; i++) {
        jump[i][0] = parentNode[i];
    }
    for (int d = 1; d < LOG_MAX; d++) {
        for (int i = 0; i < numNodes; i++) {
            if (jump[i][d - 1] != -1)
                jump[i][d] = jump[ jump[i][d - 1] ][d - 1];
            else
                jump[i][d] = -1;
        }
    }
    cout << "[LCA] Jump table initialized.\n";
}

//-------------------------
// Function: computeLCA
// Returns the Lowest Common Ancestor (LCA) of nodes u and v.
int computeLCA(int u, int v) {
    cout << "[LCA] Computing LCA for nodes " << u << " and " << v << "\n";
    if (depth[u] < depth[v])
        swap(u, v);
    // Lift node u so that depth[u] == depth[v]
    for (int d = LOG_MAX - 1; d >= 0; d--) {
        if (jump[u][d] != -1 && depth[u] - (1 << d) >= depth[v])
            u = jump[u][d];
    }
    if (u == v) {
        cout << "[LCA] LCA is " << u << "\n";
        return u;
    }
    for (int d = LOG_MAX - 1; d >= 0; d--) {
        if (jump[u][d] != jump[v][d]) {
            u = jump[u][d];
            v = jump[v][d];
        }
    }
    cout << "[LCA] LCA is " << parentNode[u] << "\n";
    return parentNode[u];
}

//-------------------------
// Function: heavyLightDFS
// Performs heavy–light decomposition: assigns each node a position in the base array
// and determines the top (head) of its heavy chain.
void heavyLightDFS(int current, int parent, int currentChainTop) {
    cout << "[HLD] Entering heavyLightDFS for node " << current 
         << " with parent " << parent << " and chain top " << currentChainTop << "\n";
    positionInBase[current] = currPos++;
    chainTop[current] = currentChainTop;

    // Find the heavy child: the child with the largest subtree.
    int heavyChild = -1;
    int heavyChildSize = -1;
    for (int child : graph[current]) {
        if (child == parent) continue;
        if (subtreeSize[child] > heavyChildSize) {
            heavyChildSize = subtreeSize[child];
            heavyChild = child;
        }
    }
    // Recurse on heavy child (same chain).
    if (heavyChild != -1)
        heavyLightDFS(heavyChild, current, currentChainTop);
    // Recurse on light children (each starts its own chain).
    for (int child : graph[current]) {
        if (child == parent || child == heavyChild) continue;
        heavyLightDFS(child, current, child);
    }
    cout << "[HLD] Leaving node " << current << "\n";
}

//-------------------------
// Function: queryPath
// Returns the maximum value on the path between nodes u and v using LCA.
int queryPath(int u, int v, int n) {
    cout << "[HLD Query] Querying path between nodes " << u << " and " << v << "\n";

    int lcaNode = computeLCA(u, v); // Step 1: Find LCA
    cout << "[Query] LCA of nodes " << u << " and " << v << " is " << lcaNode << "\n";

    int result = 0;
    
    // Query path from u to LCA
    while (chainTop[u] != chainTop[lcaNode]) {
        result = max(result, querySegmentTreeRec(1, 0, n - 1, positionInBase[chainTop[u]], positionInBase[u]));
        u = parentNode[chainTop[u]];
    }
    result = max(result, querySegmentTreeRec(1, 0, n - 1, positionInBase[lcaNode], positionInBase[u]));

    // Query path from v to LCA
    while (chainTop[v] != chainTop[lcaNode]) {
        result = max(result, querySegmentTreeRec(1, 0, n - 1, positionInBase[chainTop[v]], positionInBase[v]));
        v = parentNode[chainTop[v]];
    }
    result = max(result, querySegmentTreeRec(1, 0, n - 1, positionInBase[lcaNode], positionInBase[v]));

    cout << "[HLD Query] Path query result: " << result << "\n";
    return result;
}


//-------------------------
// Main function
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Program started.\n";
    cin >> numNodes >> numQueries;
    cout << "Number of nodes: " << numNodes 
         << ", Number of queries: " << numQueries << "\n";

    // Read node values for nodes 0 to numNodes-1
    for (int i = 0; i < numNodes; i++) {
        cin >> nodeValue[i];
        cout << "Node " << i << " value: " << nodeValue[i] << "\n";
    }
    // Read tree edges (numNodes - 1 edges)
    for (int i = 0; i < numNodes - 1; i++) {
        int u, v;
        cin >> u >> v;
        // Adjust for zero-based indexing.
        u--; v--;
        cout << "Edge: " << u << " <-> " << v << "\n";
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    // Preprocessing: compute subtree sizes, parent, and depths.
    cout << "Starting DFS to compute subtree sizes...\n";
    depth[0] = 0;
    computeSubtreeSizes(0, -1);
    cout << "DFS completed.\n";
    
    // Set up binary lifting for LCA queries.
    initializeLCA();
    
    // Perform Heavy–Light Decomposition.
    cout << "Starting Heavy Light DFS...\n";
    heavyLightDFS(0, -1, 0);
    cout << "Heavy Light DFS completed.\n";
    
    // Build the base array for the segment tree according to heavy–light order.
    // For each node, baseArray[ positionInBase[node] ] = nodeValue[node]
    vector<int> baseArray(numNodes);
    for (int i = 0; i < numNodes; i++) {
        baseArray[positionInBase[i]] = nodeValue[i];
    }
    cout << "Base array for segment tree constructed.\n";
    
    // Build the recursive segment tree over the base array.
    buildSegmentTreeRec(1, 0, numNodes - 1, baseArray);
    
    // Process queries.
    cout << "Processing queries...\n";
    while (numQueries--) {
        int queryType;
        cin >> queryType;
        if (queryType == 1) {
            int node, newValue;
            cin >> node >> newValue;
            node--;  // adjust to zero-based
            cout << "\n[Query] Update: Set node " << node << " value to " << newValue << "\n";
            nodeValue[node] = newValue;
            updateSegmentTreeRec(1, 0, numNodes - 1, positionInBase[node], newValue);
        } else {  // queryType == 2
            int u, v;
            cin >> u >> v;
            u--; v--;  // adjust to zero-based
            cout << "\n[Query] Path: Maximum value on path between nodes " << u << " and " << v << "\n";
            int result = queryPath(u, v, numNodes);
            cout << "[Query] Final result for path query: " << result << "\n";
        }
    }

    for(int i = 0; i < numNodes; i++){
        cout << positionInBase[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < numNodes; i++){
        cout << baseArray[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < 4 * numNodes; i++){
        cout << segTreeRec[i] << " ";  
    }
    
    cout << "Program finished.\n";
    return 0;
}

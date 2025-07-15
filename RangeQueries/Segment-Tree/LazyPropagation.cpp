#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100000;  // Maximum array size
long long seg[4 * MAXN];  // Segment tree
long long lazy[4 * MAXN]; // Lazy propagation array

// Build segment tree
void build(int arr[], int node, int start, int end) {
    if (start == end) {
        seg[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        seg[node] = seg[2 * node] + seg[2 * node + 1];
    }
}

// Propagate lazy updates
void propagate(int node, int start, int end) {
    if (lazy[node] != 0) {
        seg[node] += (end - start + 1) * lazy[node]; // Apply pending updates
        
        if (start != end) { // Not a leaf node
            lazy[2 * node] += lazy[node];     
            lazy[2 * node + 1] += lazy[node]; 
        }
        lazy[node] = 0; // Clear lazy update
    }
}

// Range update with lazy propagation
void updateRange(int node, int start, int end, int l, int r, int val) {
    propagate(node, start, end);
    
    if (start > r || end < l) return; // No overlap
    
    if (start >= l && end <= r) { // Complete overlap
        lazy[node] += val;
        propagate(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    updateRange(2 * node, start, mid, l, r, val);
    updateRange(2 * node + 1, mid + 1, end, l, r, val);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
}

// Range query with lazy propagation
long long queryRange(int node, int start, int end, int l, int r) {
    propagate(node, start, end);
    
    if (start > r || end < l) return 0; // No overlap
    
    if (start >= l && end <= r) return seg[node]; // Complete overlap

    int mid = (start + end) / 2;
    return queryRange(2 * node, start, mid, l, r) +
           queryRange(2 * node + 1, mid + 1, end, l, r);
}

// Driver function
int main() {
    int n, q;
    cin >> n >> q;
    
    int arr[MAXN];
    for (int i = 0; i < n; i++) cin >> arr[i];

    build(arr, 1, 0, n - 1);
    
    while (q--) {
        int type, l, r, val;
        cin >> type;
        if (type == 1) { // Update range
            cin >> l >> r >> val;
            updateRange(1, 0, n - 1, l, r, val);
        } else if (type == 2) { // Query range
            cin >> l >> r;
            cout << queryRange(1, 0, n - 1, l, r) << endl;
        }
    }
    
    return 0;
}

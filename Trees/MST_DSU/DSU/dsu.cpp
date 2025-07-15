#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1000; // Maximum number of elements (adjust as needed)

int parent[MAXN];   // Array to store parent of each element
int rankArr[MAXN];  // Renamed from 'rank' to 'rankArr' to avoid conflict

// Initialize the DSU
void initialize(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;     // Each element is its own parent
        rankArr[i] = 0;    // Initial rank is 0
    }
}

// Find function with path compression
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

// Union function with union by rank
void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rankArr[rootX] < rankArr[rootY]) {
            parent[rootX] = rootY;
        } else if (rankArr[rootX] > rankArr[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rankArr[rootX]++;
        }
    }
}

// Check if two elements are in the same set
bool isConnected(int x, int y) {
    return find(x) == find(y);
}

int main() {
    int n = 10; // Example: 10 elements (0 to 9)

    // Initialize DSU
    initialize(n);

    // Perform some union operations
    unionSets(1, 2);
    unionSets(2, 3);
    unionSets(4, 5);

    // Check connectivity
    cout << (isConnected(1, 3) ? "Connected" : "Not Connected") << endl; // Output: Connected
    cout << (isConnected(1, 4) ? "Connected" : "Not Connected") << endl; // Output: Not Connected

    return 0;
}

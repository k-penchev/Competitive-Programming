#include <iostream>
#include <vector>
using namespace std;

vector<int> fenwickTree;

void updateFenwickTree(int idx, int delta, int n) {
    while (idx <= n) {
        fenwickTree[idx] += delta;
        idx += idx & -idx;
    }
}

int queryFenwickTree(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += fenwickTree[idx];
        idx -= idx & -idx;
    }
    return sum;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int n = arr.size();
    fenwickTree.resize(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        updateFenwickTree(i + 1, arr[i], n);
    }

    int l = 1, r = 3; // Query range [1, 3]
    cout << "Fenwick Tree Range Query: " << queryFenwickTree(r) - queryFenwickTree(l - 1) << endl;
    return 0;
}

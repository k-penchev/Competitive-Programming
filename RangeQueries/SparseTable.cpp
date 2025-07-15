#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> sparseTable;
vector<int> logTable;

void buildSparseTable(vector<int>& arr) {
    int n = arr.size();
    int k = log2(n) + 1;
    sparseTable.assign(n, vector<int>(k));
    logTable.resize(n + 1);

    logTable[1] = 0;
    for (int i = 2; i <= n; ++i) logTable[i] = logTable[i / 2] + 1;

    for (int i = 0; i < n; ++i) sparseTable[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
            sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int querySparseTable(int l, int r) {
    int j = logTable[r - l + 1];
    return min(sparseTable[l][j], sparseTable[r - (1 << j) + 1][j]);
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    buildSparseTable(arr);

    int l = 1, r = 3; // Query range [1, 3]
    cout << "Sparse Table Range Query: " << querySparseTable(l, r) << endl;
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    int n = arr.size();
    vector<int> prefix(n);

    prefix[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    int l = 1, r = 3; // Query range [1, 3]
    cout << "Prefix Sum Range Query: " << (l == 0 ? prefix[r] : prefix[r] - prefix[l - 1]) << endl;
    return 0;
}

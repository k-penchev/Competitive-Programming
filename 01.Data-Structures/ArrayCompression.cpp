#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> compressArray(vector<int>& arr) {
    vector<int> sorted = arr;  // Copy the original array
    sort(sorted.begin(), sorted.end());  // Sort the copy
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());  // Remove duplicates

    vector<int> compressed(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        compressed[i] = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin() + 1;
    }
    return compressed;
}

int main() {
    vector<int> arr = {50, 10, 20, 10, 30};
    vector<int> compressed = compressArray(arr);

    // Print the compressed array
    for (int val : compressed) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

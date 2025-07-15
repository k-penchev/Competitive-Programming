#include <iostream>
#include <vector>
using namespace std;

// Function to update the BIT
void update(vector<int>& BIT, int idx, int val, int N) {
    while (idx <= N) {
        BIT[idx] += val;
        idx += idx & -idx; // Move to the next index
    }
}

// Function to query the prefix sum up to idx
int prefix_sum(const vector<int>& BIT, int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += BIT[idx];
        idx -= idx & -idx; // Move to the parent index
    }
    return sum;
}

int main() {
    int N = 1000; // Maximum value in the array
    vector<int> BIT(N + 1, 0); // BIT initialized to 0

    // Example operations
    update(BIT, 3, 1, N); // Increment count of 3
    update(BIT, 1, 1, N); // Increment count of 1
    update(BIT, 4, 1, N); // Increment count of 4
    update(BIT, 2, 1, N); // Increment count of 2
    update(BIT, 5, 1, N); // Increment count of 5
    update(BIT, 3, 1, N); // Increment count of 3 again

    // Query: Count how many values are <= 3
    cout << "Count <= 3: " << prefix_sum(BIT, 3) << endl;

    // Query: Count how many values are <= 5
    cout << "Count <= 5: " << prefix_sum(BIT, 5) << endl;

    return 0;
}

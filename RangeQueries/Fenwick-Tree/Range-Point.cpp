//Range Update - Point Query


#include <iostream>
#include <vector>
using namespace std;

// Function to update the BIT at index idx by value x
void update(vector<long long>& BIT, int idx, long long x, int N) {
    while (idx <= N) {
        BIT[idx] += x;
        idx += idx & -idx;
    }
}

// Function to get the prefix sum from 1 to idx
long long prefix_sum(const vector<long long>& BIT, int idx) {
    long long sum = 0;
    while (idx > 0) {
        sum += BIT[idx];
        idx -= idx & -idx;
    }
    return sum;
}

int main() {
    int N, Q;
    cin >> N >> Q;

    // BIT initialized with 0
    vector<long long> BIT(N + 1, 0);

    while (Q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Range update: 1 l r x
            int l, r;
            long long x;
            cin >> l >> r >> x;

            // Perform range update using BIT
            update(BIT, l, x, N);
            update(BIT, r + 1, -x, N);

        } else if (type == 2) {
            // Point query: 2 i
            int i;
            cin >> i;

            // Get the value at index i
            cout << prefix_sum(BIT, i) << endl;
        }
    }

    return 0;
}

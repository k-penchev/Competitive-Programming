// Count subgrids whose four corners are black (1)
// Bitset / popcount optimization: O(n^3 / 64)
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    const int B = 64;
    int m = (n + B - 1) / B;                 // number of 64-bit blocks per row
    vector<vector<unsigned long long>> rowbits(n, vector<unsigned long long>(m, 0ULL));

    auto read01 = [&]() -> int {
        char c;
        while (cin.get(c)) {
            if (c == '0') return 0;
            if (c == '1') return 1;
            // ignore whitespace or other separators
        }
        return -1; // EOF / bad input
    };

    // Input: n x n grid of 0/1, possibly space/newline separated
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int bit = read01();
            if (bit == -1) return 0; // input ended unexpectedly
            if (bit) {
                int g = j / B, off = j % B;
                rowbits[i][g] |= (1ULL << off);
            }
        }
    }

    long long ans = 0;
    for (int r1 = 0; r1 < n; ++r1) {
        for (int r2 = r1 + 1; r2 < n; ++r2) { // distinct rows only
            int cnt = 0;
            for (int g = 0; g < m; ++g) {
                cnt += __builtin_popcountll(rowbits[r1][g] & rowbits[r2][g]);
            }
            ans += 1LL * cnt * (cnt - 1) / 2; // choose any two columns
        }
    }

    cout << ans << '\n';
    return 0;
}

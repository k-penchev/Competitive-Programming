/**********************************************************************
 *  HIVE  —  minimise the inversion count after choosing a pivot value
 *  (problem 2269 on arena.olimpiici.com)
 *
 *  Added step-by-step logging with plain `cout`.
 *********************************************************************/

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ull = unsigned long long;

/* ------------------------- logging control ------------------------- */
#define DEBUG 1                 // 0 = silent, 1 = verbose
const int PRINT_LIMIT = 20;     // show only first PRINT_LIMIT iterations
#define LOG(x) do { if (DEBUG) { x; } } while (0)
/* ------------------------------------------------------------------- */

const int MAXN = 3 * 1'000'000 + 5;

/* ----------- globals (kept exactly as in your program) ------------- */
int          N;
int          pos[MAXN];         // pos[v] = index where value v sits
ull          lInv[MAXN], rInv[MAXN];
int          bit[MAXN];         // Fenwick tree in range 1…N
/* ------------------------------------------------------------------- */

/* -------- Fenwick helpers (unchanged) -------- */
inline void bitAdd(int idx) {
    LOG(cout << "   BIT add  @ " << idx << endl;);
    for (; idx <= N; idx += idx & -idx) bit[idx] += 1;
}
inline int bitSum(int idx) {
    int s = 0;
    for (; idx; idx -= idx & -idx) s += bit[idx];
    return s;
}
inline void bitReset() { fill(bit, bit + N + 1, 0); }
/* --------------------------------------------- */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* ----------------------- read input ------------------------ */
    cin >> N;
    LOG(cout << "Array length N = " << N << endl;);

    for (int i = 1, x; i <= N; ++i) {
        cin >> x;
        pos[x] = i;
        LOG(if (i <= PRINT_LIMIT)
            cout << "Read value " << x << " at position " << i << endl;);
    }

    /* ---------------- left-to-right sweep ---------------------- */
    LOG(cout << "\n=== LEFT SWEEP (values 1 … N) ===\n";);
    bitReset();
    ull cur = 0;                                // running inversion count
    for (int v = 1; v <= N; ++v) {
        int p   = pos[v];
        lInv[v] = cur;                          // store inversions among < v

        ull add = bitSum(N) - bitSum(p);        // new inversions by v
        cur += add;

        bitAdd(p);                              // insert v into BIT

        LOG(if (v <= PRINT_LIMIT)
            cout << "[L] v=" << v
                 << " at pos=" << p
                 << "  newInv=" << add
                 << "  cumInv=" << cur << endl;);
    }

    /* ---------------- right-to-left sweep --------------------- */
    LOG(cout << "\n=== RIGHT SWEEP (values N … 1) ===\n";);
    bitReset();
    cur = 0;
    for (int v = N; v >= 1; --v) {
        int p   = pos[v];
        rInv[v] = cur;                          // store inversions among > v

        ull add = bitSum(p - 1);                // new inversions by v
        cur += add;

        bitAdd(p);

        LOG(if (N - v + 1 <= PRINT_LIMIT)
            cout << "[R] v=" << v
                 << " at pos=" << p
                 << "  newInv=" << add
                 << "  cumInv=" << cur << endl;);
    }

    /* --------------------- take minimum ----------------------- */
    LOG(cout << "\n=== MERGE results ===\n";);
    ull answer = ULLONG_MAX;
    for (int v = 1; v <= N; ++v) {
        ull total = lInv[v] + rInv[v];
        if (total < answer) {
            answer = total;
            LOG(cout << "[M] pivot=" << v
                     << "  l=" << lInv[v]
                     << "  r=" << rInv[v]
                     << "  total=" << total
                     << "  (new best)" << endl;);
        } else {
            LOG(if (v <= PRINT_LIMIT)
                cout << "[M] pivot=" << v
                     << "  l=" << lInv[v]
                     << "  r=" << rInv[v]
                     << "  total=" << total << endl;);
        }
    }

    cout << answer << endl;
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5000 + 10;

int n;
int a[MAXN], b[MAXN], id[MAXN];
int best;

struct Fenwick
{
    int bit[MAXN];

    void set()
    {
        fill(bit, bit + 3 * n + 1, 0);
    }

    void update(int idx)
    {
        for (; idx <= 3 * n ; idx += (idx & (-idx)))
        {
            bit[idx] += 1;
        }
    }

    int query(int idx)
    {
        int s = 0;

        for (; idx >= 1 ; idx -= (idx & (-idx)))
        {
            s += bit[idx];
        }

        return s;
    }

};

Fenwick tree;
vector<vector<int>> permutations;

bool usedVal[MAXN];
vector<int> cur;   

void f(int idx, int maxA) {
    if (idx == n + 1) {
        vector<int> out(n + 1);
        out[0] = 0;
        for (int i = 1; i <= n; ++i) out[i] = cur[i];
        permutations.emplace_back(std::move(out));
        return;
    }

    
    int prev_c = (idx == 1) ? INT_MIN : (2 * (idx - 1) + cur[idx - 1]);

    
    const int C_UP = 2 * n + maxA;

    for (int v = 1; v <= n; ++v) {
        if (usedVal[v]) continue;

        int c = 2 * idx + v;
        if (c <= prev_c) continue;  
        if (c > C_UP) continue;      

        usedVal[v] = true;
        cur[idx] = v;
        f(idx + 1, maxA);
        usedVal[v] = false;
    }
}


void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        id[a[i]] = i;
    }

    
    int maxA = *max_element(a + 1, a + n + 1);
    memset(usedVal, 0, sizeof(usedVal));
    cur.assign(n + 1, 0);
    permutations.clear();
    f(1, maxA);

    best = INT_MAX;

    for (auto& perm : permutations) {
        tree.set();
        for (int i = 1; i <= n; ++i) {
            b[i] = id[perm[i]];
        }
        int currentBest = 0;
        for (int i = n; i >= 1; --i) {
            currentBest += tree.query(b[i] - 1);
            tree.update(b[i]);
        }
        best = min(best, currentBest);
    }

    cout << best << "\n";
}


void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
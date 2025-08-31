#include <bits/stdc++.h>

using namespace std;

const int MAXN = 40;
const int MAXP = 20;

int n, m;
// CHANGED: use 64-bit for GLOBAL graphs (n ≤ 40 can exceed 32-bit shifts)
vector<unsigned long long> g(MAXN), rev_g(MAXN);

// These are LOCAL (≤ 20 bits), so 32-bit is fine
vector<int> l_g(MAXP), r_g(MAXP);

// CHANGED: add left->right adjacency (in complement) with RIGHT-LOCAL bits
vector<int> l_to_r(MAXP);

// Keep validity + best size per subset
pair<bool, int> lPart[(1 << MAXP)], rPart[(1 << MAXP)];

// CHANGED: also store which submask achieves the best size (for reconstruction)
int lBest[(1 << MAXP)], rBest[(1 << MAXP)];

// CHANGED: global answer mask must be 64-bit
pair<int, unsigned long long> answer;

// calc 1) is-clique per subset  2) best size inside subset  3) best-submask (argmax)
void calc(vector<int>& adj, pair<bool, int>* result, int l, int r, int* bestMask) // CHANGED: added bestMask
{
    int len = r - l + 1;

    for (int mask = 0; mask < (1 << len); ++mask)
    {
        result[mask].first = true;
        result[mask].second = 0;
        bestMask[mask] = 0; // CHANGED: init best representative
    }

    // Check clique: for each chosen node, all other bits in mask must be in adj[node]
    for (int mask = 0; mask < (1 << len); ++mask)
    {
        for (int node = 0; node < len && result[mask].first; ++node) // CHANGED: node < len (local)
        {
            if (mask & (1 << node))
            {
                // NOTE: ((adj[node] | (1<<node)) & mask) == mask  ⇔ node adjacent to all in mask (and itself)
                if (((adj[node] | (1 << node)) & mask) != mask)
                {
                    result[mask].first = false;
                }
            }
        }
        if (result[mask].first) {
            result[mask].second = __builtin_popcount(mask);
            bestMask[mask] = mask; // CHANGED: exact clique ⇒ best is itself
        }
    }

    // SOS DP: max over submasks; propagate both size and argmax
    for (int mask = 0; mask < (1 << len); ++mask)
    {
        if (result[mask].first) continue; // already exact clique; keep it
        for (int bit = 0; bit < len; ++bit)
        {
            if (mask & (1 << bit))
            {
                int sub = mask ^ (1 << bit);
                if (result[sub].second > result[mask].second) {
                    result[mask].second = result[sub].second;
                    bestMask[mask] = bestMask[sub]; // CHANGED: carry argmax
                }
            }
        }
    }
}

void solve()
{
    cin >> n >> m;

    int x, y;

    for (int i = 0; i < m; ++i)
    {
        cin >> x >> y;

        // CHANGED: 64-bit shifts for global graph
        g[x] |= (1ULL << y);
        g[y] |= (1ULL << x);
    }

    // CHANGED: build complement within n bits and clear self-loops
    unsigned long long full = ((1ULL << n) - 1);
    for (int i = 0; i < n; ++i)
    {
        rev_g[i] = (~g[i]) & full;
        rev_g[i] &= ~(1ULL << i); // remove self
    }

    int middle = n / 2;

    int l_size = middle;
    int r_size = n - middle;

    // CHANGED: left->left (LOCAL 0..l_size-1)
    for (int i = 0; i < l_size; ++i)
    {
        unsigned long long mask = (1ULL << l_size) - 1;
        l_g[i] = (int)(rev_g[i] & mask);
    }

    // CHANGED: right->right (shift down by middle, LOCAL 0..r_size-1)
    for (int i = 0; i < r_size; ++i)
    {
        unsigned long long mask = (1ULL << r_size) - 1;
        r_g[i] = (int)((rev_g[middle + i] >> middle) & mask);
    }

    // CHANGED: left->right neighbors (RIGHT-LOCAL bits)
    for (int i = 0; i < l_size; ++i)
    {
        unsigned long long mask = (1ULL << r_size) - 1;
        l_to_r[i] = (int)((rev_g[i] >> middle) & mask);
    }

    // CHANGED: pass best-mask arrays
    calc(l_g, lPart, 0, middle - 1, lBest);
    calc(r_g, rPart, middle, n - 1, rBest);

    for (int l_mask = 0; l_mask < (1 << middle); ++l_mask)
    {
        if (lPart[l_mask].first)
        {
            // CHANGED: build allowed RIGHT mask as intersection of neighbors of all left vertices
            int allowed = (1 << r_size) - 1; // all ones in right-local space
            for (int i = 0; i < l_size; ++i)
                if (l_mask & (1 << i))
                    allowed &= l_to_r[i];

            // Size = size(left clique) + best right clique inside 'allowed'
            int total_size = lPart[l_mask].second + rPart[allowed].second;

            // CHANGED: reconstruct global node mask (left local + right local shifted)
            unsigned long long global_mask =
                (unsigned long long)lBest[l_mask] |
                ( (unsigned long long)rBest[allowed] << middle );

            answer = max(answer, make_pair(total_size, global_mask));
        }
    }

    cout << answer.first << "\n";

    for (int node = 0; node < n; ++node)
    {
        if (answer.second & (1ULL << node))
        {
            cout << node + 1 << " ";
        }
    }

    cout << "\n";
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

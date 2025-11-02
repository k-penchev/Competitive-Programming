#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long

const int MAXN = 40;
const int MAXP = 20;

int n, m;
vector<int> g(MAXN), rev_g(MAXN);

vector<int> l_g(MAXP), r_g(MAXP);

vector<int> l_to_r(MAXP);

pair<bool, int> lPart[(1ULL << MAXP)], rPart[(1ULL << MAXP)];

int lBest[(1ULL << MAXP)], rBest[(1ULL << MAXP)];

pair<int, int> answer;

void calc(vector<int>& adj, pair<bool, int> * result, int l, int r, int* bestMask)
{
    int len = r - l + 1;

    for (int mask = 0; mask < (1ULL << len); ++mask)
    {
        result[mask].first = true;
        result[mask].second = 0;
        bestMask[mask] = 0; 
    }

    for (int mask = 0; mask < (1ULL << len); ++mask)
    {
        for (int node = 0; node < len && result[mask].first; ++node) 
        {
            if (mask & (1ULL << node))
            {
                if (((adj[node] | (1ULL << node)) & mask) != mask)
                {
                    result[mask].first = false;
                }
            }
        }
        if (result[mask].first) {
            result[mask].second = __builtin_popcount(mask);
            bestMask[mask] = mask; 
        }
    }

    for (int mask = 0; mask < (1ULL << len); ++mask)
    {
        if (result[mask].first) continue; 
        for (int bit = 0; bit < len; ++bit)
        {
            if (mask & (1ULL << bit))
            {
                int sub = mask ^ (1ULL << bit);
                if (result[sub].second > result[mask].second) {
                    result[mask].second = result[sub].second;
                    bestMask[mask] = bestMask[sub];
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

        g[x] |= (1ULL << y);
        g[y] |= (1ULL << x);
    }

    
    int full = ((1ULL << n) - 1);
    for (int i = 0; i < n; ++i)
    {
        rev_g[i] = (~g[i]) & full;
        rev_g[i] &= ~(1ULL << i); 
    }

    int middle = n / 2;

    int l_size = middle;
    int r_size = n - middle;

    for (int i = 0; i < l_size; ++i)
    {
        int mask = (1ULL << l_size) - 1;
        l_g[i] = (rev_g[i] & mask);
    }

    for (int i = 0; i < r_size; ++i)
    {
        int mask = (1ULL << r_size) - 1;
        r_g[i] = ((rev_g[middle + i] >> middle) & mask);
    }

    for (int i = 0; i < l_size; ++i)
    {
        int mask = (1ULL << r_size) - 1;
        l_to_r[i] = ((rev_g[i] >> middle) & mask);
    }

    calc(l_g, lPart, 0, middle - 1, lBest);
    calc(r_g, rPart, middle, n - 1, rBest);

    for (int l_mask = 0; l_mask < (1ULL << middle); ++l_mask)
    {
        if (lPart[l_mask].first)
        {
            int allowed = (1ULL << r_size) - 1; 
            for (int i = 0; i < l_size; ++i)
                if (l_mask & (1ULL << i))
                    allowed &= l_to_r[i];

            int total_size = lPart[l_mask].second + rPart[allowed].second;

            int global_mask = lBest[l_mask] | (rBest[allowed] << middle);

            answer = max(answer, make_pair(total_size, global_mask));
        }
    }

    cout << answer.first << "\n";

    for (int node = 0; node < n; ++node)
    {
        if (answer.second & (1ULL << node))
        {
            cout << node << " ";
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

signed main()
{
    fastIO();
    solve();
}

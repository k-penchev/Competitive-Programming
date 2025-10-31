//fenwick tree for sum (with values being only 0s and 1s)
//this is known as "compressed fenwick tree"
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int LOG = 20 + 1;

int n;

struct Fenwick
{
    int bit[MAXN];

    void set()
    {
        std::fill(bit + 1, bit + n + 1, 0);
    }

    void update(int idx, int val)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] += val;
        }
    }

    int queryPoint(int idx)
    {
        int s = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            s += bit[idx];
        }

        return s;
    }

    int querySmallerThan(int idx)
    {
        return queryPoint(idx - 1);
    }

    int queryBiggerThan(int idx)
    {
        return queryPoint(n) - queryPoint(idx);
    }

    //findKth can be used here, too
};

Fenwick tree;

void solve()
{
    std::cin >> n;

    tree.set();
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
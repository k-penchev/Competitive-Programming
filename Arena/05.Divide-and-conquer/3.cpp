#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 5;

int n;
int a[MAXN];

struct Fenwick
{
    int bit[MAXN];

    void set()
    {
        std::fill(bit + 1, bit + n + 1, 0);
    }

    void update(int idx)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] += 1;
        }
    }

    int query(int idx)
    {
        int s = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            s += bit[idx];
        }

        return s;
    }
};


struct MergeSortTree
{
    struct Node
    {
        Fenwick tree;
    };

    void build(int idx, int l, )
    {

    }

    void update()
    {

    }

    Node query()
    {

    }
};

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    for(int i = 1 ; i <= n - 2 ; ++i)
    {
        int x;
        std::cin >> x;
    }
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
    
    return 0;
}
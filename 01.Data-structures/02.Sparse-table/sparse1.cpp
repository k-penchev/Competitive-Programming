//sparse table for range min / max / gcd / lcm
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int LOG = 20 + 1;

int n;
int a[MAXN];

struct Sparse
{
    int table[MAXN][LOG];
    int log[MAXN];

    void build(int * arr)
    {
        log[1] = 0;

        for(int i = 2 ; i <= n ; ++i)
        {
            log[i] = log[i / 2] + 1;
        }

        for(int i = 1 ; i <= n ; ++i)
        {
            table[i][0] = arr[i];
        }

        for(int j = 1 ; (1 << j) <= n ; ++j)
        {
            for(int i = 1 ; i + (1 << j) - 1 <= n ; ++i)
            {
                table[i][j] = std::min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r)
    {
        int j = log[r - l + 1];
        return std::min(table[l][j], table[r - (1 << j) + 1][j]);
    }
};

Sparse table;

void solve()
{
    std::cin >> n;
    
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    table.build(a);

    std::cout << table.query(1, 5) << " " << table.query(1, 6) << "\n";
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
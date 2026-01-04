//sparse table for sums
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
                table[i][j] = table[i][j - 1] + table[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    int query(int l, int r)
    {
        int s = 0;

        for(int j = LOG - 1 ; j >= 0 ; --j)
        {
            if((1 << j) <= r - l + 1)
            {
                s += table[l][j];
                l += (1 << j);
            }
        }

        return s;
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

    std::cout << table.query(1, 2) << " " << table.query(3, 5) << "\n";
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
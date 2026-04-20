#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1000;
const int MAXLOG = 10 + 1;

int n;
int a[MAXN];

struct Sparse
{
    int last;
    int mask[MAXN];
    int table[MAXN][MAXLOG];
    

    int f(int x, int y)
    {
        return x + y;
    }

    void divide(int l, int r, int level, int arr[])
    {
        if(l == r)
        {
            last = level;
            table[l][level] = arr[l];
            return;
        }

        int mid = (l + r) / 2;
        divide(l, mid, level + 1, arr); 
        divide(mid + 1, r, level + 1, arr);

        table[mid][level] = arr[mid];
        for(int i = mid - 1 ; i >= l ; --i)
        {
            table[i][level] = f(arr[i], table[i + 1][level]);
        }

        table[mid + 1][level] = arr[mid + 1];
        for(int i = mid + 2 ; i <= r ; ++i)
        {
            table[i][level] = f(table[i - 1][level], arr[i]);
        }

        for(int i = mid + 1 ; i <= r ; ++i)
        {
            mask[i] |= (1 << level);
        }
    }

    void build(int arr[])
    {
        std::fill(mask, mask + n, 0);
        divide(0, n - 1, 0, arr);
    }

    int query(int l, int r)
    {
        if(l == r)
        {
            return table[l][last];
        }

        int level = __builtin_ctz(mask[l] ^ mask[r]);
        return f(table[l][level], table[r][level]);
    }
};

Sparse table;

void solve()
{
    std::cin >> n;

    for(int i = 0 ; i < n ; ++i)
    {
        std::cin >> a[i];
    }

    table.build(a);

    std::cout << table.query(0, 3) << " " << table.query(3, 7) << "\n";
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

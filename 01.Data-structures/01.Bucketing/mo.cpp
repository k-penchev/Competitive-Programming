#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int BUCKET = 320;

int n, q;
int a[MAXN];

void solve()
{
    std::cin >> n;
    
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    std::cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        int l, r;
        std::cin >> l >> r;
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
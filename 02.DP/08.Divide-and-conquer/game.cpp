#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 4 * 1e4 + 10;

int t, n;
long long a[MAXN];
long long prefix[MAXN];

bool check(int blockL, int blockR, int split)
{
    return ((prefix[split] - prefix[blockL - 1]) <= ((prefix[blockR] - prefix[blockL - 1]) / 2));
}

int divide(int l, int r)
{
    if(l >= r)
    {
        return 0;
    };

    if(((prefix[r] - prefix[l - 1]) % 2) != 0)
    {
        return 0;
    } 
    
    int lPtr = l, rPtr = r;
    while(lPtr + 1 < rPtr)
    {
        int binary_mid = (lPtr + rPtr) / 2;

        if(check(l, r, binary_mid)) lPtr = binary_mid;
        else rPtr = binary_mid;
    }

    if((prefix[lPtr] - prefix[l - 1]) != ((prefix[r] - prefix[l - 1]) / 2))
    {
        return 0;
    }

    return 1 + std::max(divide(l, lPtr), divide(lPtr + 1, r));
}

void solve()
{
    std::cin >> t;

    for(int i = 1 ; i <= t ; ++i)
    {
        std::cin >> n;

        for(int j = 1 ; j <= n ; ++j)
        {
            std::cin >> a[j];
        }

        prefix[1] = a[1];
        for(int j = 2 ; j <= n ; ++j)
        {
            prefix[j] = prefix[j - 1] + a[j];
        }
        
        std::cout << divide(1, n) << "\n"; 
    }
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
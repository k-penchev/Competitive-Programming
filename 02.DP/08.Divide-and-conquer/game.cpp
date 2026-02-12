#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 20000 + 10;
const int INF = 1e9 + 10;

int n;
int a[MAXN];
int prefix[MAXN];

bool check(int l, int r, int split)
{
    return prefix[split] - prefix[l - 1] <= (prefix[r] - prefix[l - 1]) / 2;
}

int divide(int l, int r)
{
    if(l >= r)
    {
        return 0;
    }

    if(((prefix[r] - prefix[l - 1]) % 2) != 0)
    {
        return 0;
    }

    int lPtr = l, rPtr = r, mid;
    while(lPtr + 1 < rPtr)
    {
        int mid = lPtr + rPtr >> 1;
        if(check(l, r, mid)) lPtr = mid;
        else rPtr = mid;
    }

    if(prefix[lPtr] - prefix[l - 1] != (prefix[r] - prefix[l - 1]) / 2)
    {
        return 0;
    }

    return 1 + std::max(divide(l, lPtr), divide(lPtr + 1, r));
}

int tests;
void solve()
{
    std::cin >> tests;
    while(tests--)
    {
        std::cin >> n;
        for(int i = 1 ; i <= n ; ++i)
        {
            std::cin >> a[i];
        }

        prefix[1] = a[1];
        for(int i = 2 ; i <= n ; ++i)
        {
            prefix[i] = prefix[i - 1] + a[i];
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
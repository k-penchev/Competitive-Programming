#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 100000 + 10;
const int INF = 1e9 + 10;
const int MOD = 1e9 + 7;

int power(int num, int base)
{
    if(base == 0)
    {
        return 1;
    }

    if(base & 1)
    {
        return num * power(num, base - 1);
    }

    int res = power(num, base >> 1);
    return res * res;
}

int power2(int num, int base)
{
    int res = 1;
    for(int lg = 0 ; lg < 31 ; ++lg)
    {
        if((base >> lg) & 1)
        {
            res = res * num;
        }

        num = num * num;
    }

    return res;
}

void solve()
{
    int num, base;
    std::cin >> num >> base;
    std::cout << power(num, base) << "\n";
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
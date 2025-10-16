#include <iostream>
#include <algorithm>
#include <vector>

long long calcAns(long long  x)
{
    if(x % 2 == 0)
    {
        return 2;
    }

    for(long long i = 3 ; i * i <= x ; i += 2)
    {
        if(x % i == 0)
        {
            return i;
        }
    }

    return x;
}

void solve()
{
    long long a;
    while(std::cin >> a)
    {
        std::cout << calcAns(a) << "\n";
    }

    std::cout << "\n";
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
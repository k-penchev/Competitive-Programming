#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int INTINF = 1e9 + 10;

int n;
bool prime[MAXN];

void sieve()
{
    for(int i = 2 ; i <= n ; ++i)
    {
        prime[i] = true;
    }

    for(int i = 2 ; i * i <= n ; ++i)
    {
        if(prime[i])
        {
            for(int j = i * i ; j <= n ; j += i)
            {
                prime[j] = false;
            }
        }
    }
}

void solve()
{
    std::cin >> n;
    sieve();
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
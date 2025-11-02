#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

const int MAXN = 1e5 + 10;

auto SEED = std::chrono::steady_clock::now().time_since_epoch().count();
std::mt19937 rng(SEED);

int n;
int a[MAXN];

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    std::shuffle(a + 1, a + n + 1, rng);
    
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << a[i] << " ";
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
    
    return 0;
}
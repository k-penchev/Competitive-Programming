#include <iostream>
#include <algorithm>
#include <vector>

int n;

std::vector<int> factorization(int x)
{
    std::vector<int> res;

    for(int i = 2 ; i * i <= x ; ++i)
    {
        while(x % i == 0)
        {
            res.push_back(i);
            x /= i;
        }
    }

    if(x > 1) res.push_back(x);
    return res;
}

void solve()
{
    std::cin >> n;

    auto res = factorization(n);
    for(auto &f : res)
    {
        std::cout << f << " ";
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
//bitmask
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 20 + 5;
const int MOD = 1e9 + 7;

int n;
int a[MAXN];

void solve()
{
    std::cin >> n;
    assert(n <= 20);

    for(int i = 0 ; i < n ; ++i)
    {
        std::cin >> a[i];
    }

    long long answer = 0;
    for(int mask = 1 ; mask < (1 << n) ; ++mask)
    {
        std::vector<int> v;
        for(int i = 0 ; i < n ; ++i)
        {
            if(mask & (1 << i))
            {
                v.push_back(a[i]);
            }
        }

        long long current = 0;
        for(int i = 0 ; i < v.size() ; ++i)
        {
            if(i != v.size() - 1)
            {
                if(v[i] != v[i + 1])
                {
                    current += 1;
                }
            }
        }

        current += 1;
        answer = (answer + current) % MOD;
    }

    std::cout << answer << "\n";
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
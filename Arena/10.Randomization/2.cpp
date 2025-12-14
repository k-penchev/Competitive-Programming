#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <unordered_map>

#define int long long

const int MAXN = 1e6 + 10;

int n;
int a[MAXN];
std::unordered_map<int,int> f;
std::unordered_map<int,int> cnt;

int compute()
{
    int idx = rand() % n;

    std::vector<int> divs;
    for(int i = 1 ; i * i <= a[idx] ; ++i)
    {
        if(a[idx] % i == 0)
        {
            divs.push_back(i);

            if(i * i != a[idx])
            {
                divs.push_back(a[idx] / i);
            }
        }
    }

    for(int i = 0 ; i < n ; ++i)
    {
        f[std::__gcd(a[i], a[idx])] += 1;
    }   

    std::sort(divs.begin(), divs.end());

    int max = -1;
    for(int i = 0 ; i < divs.size() ; ++i)
    {
        for(int j = i ; j < divs.size() ; ++j)
        {
            if(divs[j] % divs[i] == 0)
            {
                cnt[divs[i]] += f[divs[j]];
            }
        }

        if(cnt[divs[i]] >= ((n + 1) / 2))
        {
            max = std::max(max, divs[i]);
        }
    }

    return max;
}

void reset()
{
    f.clear();
    cnt.clear();
}

void solve()
{
    std::cin >> n;

    for(int i = 0 ; i < n ; ++i)
    {
        std::cin >> a[i];
    }

    int ans = -1;
    for(int i = 0 ; i < 12 ; ++i)
    {
        ans = std::max(ans, compute());
        reset();
    }

    std::cout << ans << "\n";
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
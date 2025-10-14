#include <iostream>
#include <algorithm>
#include <vector>


const int MAXN = 1e5 + 10;
const int MAXK =  (1 << 20) + 5;;
const int SQRT = 320;

int n, m, k;
long long a[MAXN], pref[MAXN], ans[MAXN];
long long cnt[MAXK], total = 0;

struct Query
{
    int idx;
    int l;
    int r;
};

std::vector<Query> query;

void add(int idx)
{
    total += cnt[pref[idx] ^ k];
    cnt[pref[idx]] += 1;
}

void remove(int idx)
{
    cnt[pref[idx]] -= 1;
    total -= cnt[pref[idx] ^ k];
}

void solve()
{
    std::cin >> n >> m >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    pref[1] = a[1];
    for(int i = 2 ; i <= n ; ++i)
    {
        pref[i] = pref[i - 1] ^ a[i];
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        query.push_back({i, l - 1, r});
    }

    std::sort(query.begin(), query.end(), [&](const Query& a, const Query& b)
    {
        int bucket_a = a.l / SQRT;
        int bucket_b = b.l / SQRT;

        if(bucket_a == bucket_b)
        {
            return a.r < b.r;
        }

        return bucket_a < bucket_b;
    });

    int lPtr = 1, rPtr = 0;
    for(auto& [idx, l, r] : query)
    {
        //add l
        while(lPtr > l)
        {
            add(--lPtr);
        }

        //add r
        while(rPtr < r)
        {
            add(++rPtr);
        }

        //remove l
        while(lPtr < l)
        {
            remove(lPtr++);
        }

        //remove r
        while(rPtr > r)
        {
            remove(rPtr--);
        }

        ans[idx] = total;
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        std::cout << ans[i] << "\n";
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
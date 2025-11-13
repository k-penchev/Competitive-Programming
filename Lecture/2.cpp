//compression
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

#define int long long

const int MAXN = 1e5 + 10;
const int MAXV = 4 * MAXN;

int n, q;
int values;

struct Update
{
    int l;
    int r;
    int v;
};

struct Query
{
    int l;
    int r;
};

Update update[MAXN];
Query query[MAXN];
std::vector<int> vec;
std::vector<int> coord;
std::unordered_map<int, int> map;

int difference[MAXV];
int val[MAXV];
int prefix[MAXV];

void compress()
{
    std::sort(vec.begin(), vec.end());

    int cnt = 1;
    for(int i = 0 ; i < vec.size() ; ++i)
    {
        map[vec[i]] = cnt;
        if(i != vec.size() - 1)
        {
            if(vec[i] != vec[i + 1])
            {
                cnt += 1;
            }
        }

        if(coord.empty() || vec[i] != coord.back())
        {
            coord.push_back(vec[i]);
        }
    }

    values = cnt;
}

void solve()
{
    std::cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        int l, r, v;
        std::cin >> l >> r >> v;

        update[i] = {l, r, v};
        vec.push_back(l);
        vec.push_back(r);
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int l, r;
        std::cin >> l >> r;

        query[i] = {l, r};
        vec.push_back(l);
        vec.push_back(r);
    }

    compress();

    for(int i = 1 ; i <= n ; ++i)
    {
        auto &[l, r, v] = update[i];

        difference[map[l]] += v;
        difference[map[r]] -= v;
    }

    for(int i = 1 ; i <= values ; ++i)
    {
        val[i] = val[i - 1] + difference[i];
    }

    for(int i = 2 ; i <= values ; ++i)
    {
        int len = coord[i - 1] - coord[i - 2]; 
        prefix[i] = prefix[i - 1] + val[i - 1] * len;
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        auto &[l, r] = query[i];
        std::cout << prefix[map[r]] - prefix[map[l]] << "\n";
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
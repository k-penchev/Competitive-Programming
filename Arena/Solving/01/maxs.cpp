#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 5 * 1e4 + 10;
const int MAXM = 5 * 1e5 + 10;
const int INF = 1e18 + 10;

int n, q;
int a[MAXN];
int chainAt[MAXN];
std::pair<int, int> sorted[MAXN];
int with[MAXN];
int without[MAXN];
int ans;

int query(int pos, int s)
{
   return std::max(with[pos] + s, without[pos]);
}

void build()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = i ; j <= n ; j += i)
        {
            chainAt[i] += a[j];
        }
    }

    std::fill(with + 1, with + n + 1, -INF);
    std::fill(without + 1, without + n + 1, -INF);

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = i ; j <= n ; j += i)
        {
            with[j] = std::max(with[j], chainAt[i]);
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        sorted[i] = {chainAt[i], i};
    }

    std::sort(sorted + 1, sorted + n + 1);
    std::reverse(sorted + 1, sorted + n + 1);

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            if(i % sorted[j].second != 0)
            {
                without[i] = sorted[j].first;
                break;
            }
        }
    }
}

void solve()
{
    std::cin >> n;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    build();
    std::cin >> q;
    for(int i = 1 ; i <= q ; ++i)
    {
        int pos, s;
        std::cin >> pos >> s;
        ans += query(pos, s);
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
}
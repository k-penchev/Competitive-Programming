#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 80 + 10;
const int MAXK = 80 + 10;
const int MAXT = 250 + 10;
const int MAXS = MAXK * MAXT + 10;
const int INF = 1e18 + 10;

int n, k;

struct Person
{
    int w;
    int t;
};

Person p[MAXN];
int dp[MAXN][MAXK][MAXS];
bool memo[MAXN][MAXK][MAXS];

int f(int pos, int cnt, int t)
{
    if(cnt < 0) return INF;
    if(pos == n + 1 && cnt == 0) return 0;
    else if(pos == n + 1) return INF;

    if(memo[pos][cnt][t]) return dp[pos][cnt][t];

    memo[pos][cnt][t] = 1;

    dp[pos][cnt][t] = std::min(f(pos + 1, cnt, t), std::max(p[pos].w + t, f(pos + 1, cnt - 1, t + p[pos].t)));
    return dp[pos][cnt][t];
}

void solve()
{
    std::cin >> n >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> p[i].w >> p[i].t;
    }

    std::sort(p + 1, p + n + 1, [&](const Person& a, const Person& b)
    {
        int f = std::max(a.w, b.w + a.t);
        int s = std::max(b.w, a.w + b.t);

        return f <= s;
    });

    std::cout << f(1, k, 0) << "\n";
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
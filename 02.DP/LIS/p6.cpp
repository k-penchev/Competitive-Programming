#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int INF = 1e18;

int N;

struct Candy
{
    int l;
    int r;
};

Candy candy[MAXN];
int dp[MAXN];
vector<int> resultByLen[MAXN];

int lower_binary(int x)
{
    int l = -1, r = N;
    
    while(r > l + 1)
    {
        int m = (l + r) / 2;

        if(dp[m] >= x)
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }

    return r;
}

void solve()
{
    cin >> N;

    int s, t;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> s >> t;
        candy[i] = {s - t, s + t};
    }

    sort(candy, candy + N, [&](const Candy& c1, const Candy& c2)
    {
        if(c1.l == c2.l)
        {
            return c1.r > c2.r;
        }

        return c1.l < c2.l;
    });

    for(int i = 0 ; i <= N ; ++i)
    {
        dp[i] = INF;    
    }

    dp[0] = -INF;

    for(int i = 0 ; i < N ; ++i)
    {
        int x = candy[i].r;

        int idx = lower_binary(x);

        dp[idx] = x;
        
        resultByLen[idx].push_back(i);
    }

    int lis = 0;

    for(int i = 1 ; i <= N; ++i)
    {
        if(dp[i] < INF)
        {
            lis = i;
        }
    }

    cout << lis << "\n";

    for(int i = 1 ; i <= lis ; ++i)
    {
        for(int j : resultByLen[i])
        {
            int s = (candy[j].l + candy[j].r) / 2;
            int t = candy[j].r - s;

            cout << s << " " << t << " " << i << "\n";
        }
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
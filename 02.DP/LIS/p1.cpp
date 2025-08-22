/*

Classic result: the minimum number of increasing subsequences 
needed to cover T equals the 
length of the Longest Decreasing Subsequence (LDS) of T.


LDS(x) = LIS(-X)

*/

#include <bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e9;
const int MAXN = 1e5 + 10;

int n;
int dp[MAXN];

struct Wire
{
    int x1;
    int x2;
};

Wire wire[MAXN];
int layers = 0;

int binary(int x)
{
    int lPtr = -1, rPtr = n;

    while(rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(dp[mid] >= x)
        {
            rPtr = mid;
        }
        else
        {
            lPtr = mid;
        }
    }


    return rPtr;
}

void solve()
{
    cin >> n;
    
    for(int i = 0 ; i < n ; ++i)
    {
        cin >> wire[i].x1 >> wire[i].x2;
    }

    sort(wire, wire + n, [&](const Wire& w1, const Wire& w2)
    {
        if(w1.x1 == w2.x1)
        {
            return w1.x2 < w2.x2;
        }

        return w1.x1 < w2.x1;
    });

    for(int i = 0 ; i <= n ; ++i)
    {
        dp[i] = +INF;
    }

    dp[0] = -INF;

    for(int i = 0 ; i < n ; ++i)
    {
        int x = -wire[i].x2;

        int l = binary(x);

        dp[l] = x;

    }

    for(int i = 0 ; i <= n ; ++i)
    {
        if(dp[i] < INF)
        {
            layers = i;
        }
    }

    cout << layers << "\n";
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
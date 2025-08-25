#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
const int INF = 1e9;

int n;

struct Line
{
    int x;
    int y;
};

Line a[MAXN];
int sorted[MAXN];
int dp[MAXN];

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
        cin >> a[i].x;
    }

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> a[i].y;
    }

    sort(a, a + n, [&](const Line& l1, const Line& l2)
    {
        return l1.x < l2.x;
    });

    iota(sorted, sorted + n, 0);
    sort(sorted, sorted + n, [&](int x, int y)
    {
        return a[x].y < a[y].y;
    });

    for(int i = 0 ; i <= n ; ++i)
    {
        dp[i] = INF;
    }

    dp[0] = -INF;

    for(int i = 0 ; i < n ; ++i)
    {
        int l = binary(sorted[i]);

        dp[l] = sorted[i];
    }

    int lis = 0;

    for(int i = 0 ; i <= n ; ++i)
    {
        if(dp[i] < INF)
        {
            lis = i;
        }
    }

    cout << lis << "\n";
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
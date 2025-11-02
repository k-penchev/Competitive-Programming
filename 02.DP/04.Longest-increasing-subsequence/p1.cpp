#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 2 * 1e5 + 10;
const int INF = 1e9;

int n;
int a[MAXN];
int dp[MAXN];
int answer = 0;

int upper_binary_search(int x)
{
    int lPtr = -1, rPtr = n;

    while(rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(dp[mid] > x)
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

int LongestNonDecresing()
{
    for(int i = 0 ; i <= n ; ++i)
    {
        dp[i] = INF;
    }

    dp[0] = -INF;
    
    for(int i = 0 ; i < n ; ++i)
    {
        int l = upper_binary_search(a[i]);

        dp[l] = a[i];
    }

    for(int i = 0 ; i <= n ; ++i)
    {
        if(dp[i] < INF)
        {
            answer = i;
        }
    }

    return answer;
}

void solve()
{
    cin >> n;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> a[i];
    }

    cout << LongestNonDecresing() << "\n";
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
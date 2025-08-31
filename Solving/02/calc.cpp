#include <bits/stdc++.h>

using namespace std;

const int MAXN = 70 + 5;
const int MAXA = 1000 + 10;
const int MAXS = MAXN * MAXA;

int n;
long long dp[MAXN][MAXS];
int nums[MAXN];

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> nums[i];
    }

    sort(nums + 1, nums + n + 1, [&](int x, int y)
    {
        return x > y;
    });

    dp[0][0] = 1;
    
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int s = 0 ; s < MAXS ; ++s)
        {
            dp[i][s] = dp[i - 1][s];
            
            if(s >= nums[i])
                dp[i][s] += dp[i - 1][s - nums[i]];
        }
    }

    long long sumsCnt = 0, bestSum = 0, bestCnt = 0;

    for(int s = 1 ; s < MAXS ; ++s)
    {
        sumsCnt += (dp[n][s] ? 1 : 0);

        if(dp[n][s] >= bestCnt)
        {
            bestCnt = dp[n][s];
            bestSum = s;
        }
    }

    cout << sumsCnt << "\n";

    cout << bestSum << " " << bestCnt << "\n";

    for(int i = n ; i >= 1 ; --i)
    {
        int x = nums[i];

        if(bestSum >= x && dp[i - 1][bestSum - x] > 0)
        {
            cout << x << " ";
            bestSum -= x;
        }
    }

    cout << "\n";
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
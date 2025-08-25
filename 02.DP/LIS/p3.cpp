#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int INF = 1e9;

int n;
int perm1[MAXN], perm2[MAXN];

void solve()
{
    cin >> n;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> perm1[i];
    }

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> perm2[i];
    }

    vector<int> dp(n + 1);

    for(int i = 0 ; i < n ; ++i)
    {
        int bestLen = 0;

        for(int j = 0 ; j < n ; ++j)
        {
            if(perm1[i] == perm2[j])
            {
                if(bestLen + 1 > dp[j])
                {
                    dp[j] = bestLen + 1;
                }
            }
            else if(perm2[j] < perm1[i])
            {
                if(dp[j] > bestLen)
                {
                    bestLen = dp[j];
                }
            }
        }
    }

    int lis = 0;

    for(int j = 0 ; j <= n ; ++j)
    {
        lis = max(lis, dp[j]);
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
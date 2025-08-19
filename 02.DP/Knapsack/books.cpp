#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 10;
const int MAXX = 1e5 + 10;

int n, x;
int price[MAXN], pagesCnt[MAXN];
int dp[MAXX];
int answer = 0;

void solve()
{
    cin >> n >> x;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> price[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> pagesCnt[i];
    }

    for(int item_idx = 1 ; item_idx <= n ; ++item_idx)
    {
        for(int total_price = x - 1 ; total_price >= 0 ; --total_price)
        {
            if(total_price + price[item_idx] <= x)
            {
                dp[total_price + price[item_idx]] = max(dp[total_price + price[item_idx]], dp[total_price] + pagesCnt[item_idx]);
            }
        }     
    }

    for(int i = 0 ; i <= x ; ++i)
    {
        answer = max(answer, dp[i]);
    }

    cout << answer << "\n";
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
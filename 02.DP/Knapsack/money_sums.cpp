#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e2 + 10;
const int MAXS = 1e5 + 10;

int n;
vector<int> coins, answer;
bool dp[MAXN * MAXS];

void solve()
{
    cin >> n;

    dp[0] = true;

    for(int i = 0 ; i < n ; ++i)
    {
        int c; cin >> c;
        for(int sum = MAXS ; sum >= 0 ; --sum)
        {
            if(dp[sum])
            {
                dp[sum + c] = true;
            }
        }

    }

    for(int i = 1 ; i < MAXN * MAXS ; ++i)
    {
        if(dp[i])
        {
            answer.push_back(i);
        }
    }
    
    cout << answer.size() << "\n";

    for(int a : answer)
    {
        cout << a << " ";
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
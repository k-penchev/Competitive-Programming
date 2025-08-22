#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e2;
const int MAXI = 1e3;
const int MAXS = MAXN * MAXI + 1;

int n;
vector<int> answer;

void solve()
{
    cin >> n;

    vector<bool> dp(MAXS, 0);

    dp[0] = true;

    int coin;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> coin;

        for(int j = MAXS ; j >= 0 ; --j)
        {
            if(dp[j])
            {
                dp[j + coin] = true;
            }
        }
    }

    
    for(int i = 1 ; i <= MAXS ; ++i)
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
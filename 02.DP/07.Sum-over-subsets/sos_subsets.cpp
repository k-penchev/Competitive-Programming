#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

int n;
int arr[(1 << MAXN)];
int dp[(1 << MAXN)];

void print_in_binary(int num)
{
    for(int bit = 20 ; bit >= 0 ; --bit)
    {
        if(num & (1 << bit)) cout << "1";
        else cout << "0";
    }
}

void solve()
{
    cin >> n;

    for(int mask = 0 ; mask < (1 << n) ; ++mask)
    {
        cin >> arr[mask];
    }

    
    for(int mask = 0 ; mask < (1 << n) ; ++mask)
    {
        dp[mask] = arr[mask];
    }
    
    for(int bit = 0 ; bit < n ; ++bit)
    {
        for(int mask = 0 ; mask < (1 << n) ; ++mask)
        {
            if(mask & (1 << bit))
            {
                dp[mask] += dp[mask ^ (1 << bit)];
            }
        }
    }

    for(int mask = 0 ; mask < (1 << n) ; ++mask)
    {
        print_in_binary(mask);
        cout << " " << dp[mask] << "\n";
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
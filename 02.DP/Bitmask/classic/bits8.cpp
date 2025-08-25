//Dynamic programming
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

int N;
int element[MAXN];
int sum[(1 << MAXN)];

void solve()
{
    cin >> N;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> element[i];
    }

    for(int i = 0 ; i < N ; ++i)
    {
        sum[(1 << element[i])] = element[i];
    }

    for(int subset = 0 ; subset < (1 << MAXN) ; ++subset)
    {
        
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
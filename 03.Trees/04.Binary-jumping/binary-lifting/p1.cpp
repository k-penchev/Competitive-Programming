#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;
const int MAXLOG = 30 + 1;

int n, q;
int teleport[MAXN];
int lift[MAXN][MAXLOG];

void precompute()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        lift[i][0] = teleport[i];
    }
    
    for(int j = 1 ; j < MAXLOG ; ++j)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            int prev = lift[i][j - 1];
            lift[i][j] = lift[prev][j - 1];
        }
    }
}

int query(int x, int k)
{
    int result = x;

    for(int i = 0 ; i < MAXLOG ; ++i)
    {
        if(k & (1 << i))
        {
            result = lift[result][i];
        }
    }

    return result;
}

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> teleport[i];
    }

    precompute();

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int x, k; cin >> x >> k;
        cout << query(x, k) << "\n";
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
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2500000 + 10;

int n;
int a[MAXN];
int xorVal = 0;

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        xorVal ^= a[i];
    }

    int mask = (xorVal & (-xorVal));
    int x = 0, y = 0;

    for(int i = 1 ; i <= n ; ++i)
    {
        if((a[i] & mask) == 0)
        {
            x ^= a[i];
        }
        else
        {
            y ^= a[i];
        }
    }

    if(x > y) swap(x, y);

    cout << x << " " << y << "\n";
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
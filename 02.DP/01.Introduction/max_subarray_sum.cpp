#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;

int n;
int a[MAXN];

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
    }

    int res = a[1], maxEnding = a[1];
    int l = 0, r = 0;

    for(int i = 2 ; i <= n ; ++i)
    {
        maxEnding = max(a[i], maxEnding + a[i]);

        res = max(res, maxEnding);
    }

    for(int i = 2 ; i <= n ; ++i)
    {
        maxEnding = max(a[i], maxEnding + a[i]);

        res = max(res, maxEnding);
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
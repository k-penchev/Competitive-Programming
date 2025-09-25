#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long llong;

llong n;

void solve()
{
    cin >> n;

    llong R = n % 300;

    if(R == 0)
    {
        cout << "00" << "\n";
        return;
    }

    llong a = 0, b = 1;

    for(int i = 1 ; i <= R ; ++i)
    {
        llong next = (a + b) % 100;

        a = b;
        b = next;
    }

    cout << a << "\n";
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
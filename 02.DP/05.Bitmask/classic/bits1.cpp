//Bit representation
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    /*
    
    signed [-2^(n-1) ; +2^(n-1)-1]
    unsigned [0 ; +2^n-1]

    */

    
    //signed -x == unsigned 2^n - x
    int x = -43;
    unsigned int y = x;

    cout << x << "\n";
    cout << y << "\n";
    
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
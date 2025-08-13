#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int MAXQ = 2 * 1e6 + 10;
const int MAX_LOG = 30;

int n, q;
int a[MAXN];

void solve()
{
    cin >> n >> q;


    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
    }

    char qType;
    int l, r, x;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> qType >> l >> r;

        if(qType == '&')
        {
            cin >> x;
            
            
        }
        else if(qType == '|')
        {
            cin >> x;
            
            
        }
        else
        {
            int answer = 0;

            

            cout << answer << "\n";
        }

    }
}


void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
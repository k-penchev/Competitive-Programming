#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, m;
int cnt = 0;

set<int> friends[MAXN];

int compute()
{
    int ret = 0;    

    for(int x = 1 ; x <= n ; ++x)
    {
        int exchange = 0;

        for(int y : friends[x])
        {
            for(int z : friends[y])
            {
                if(y != z)
                {
                    if(friends[z].find(y) != friends[z].end())
                    {
                        ++exchange;
                    }
                }
            }
        }

        ret = max(ret, exchange);
    }

    return ret;
}

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b; cin >> a >> b; ++cnt;
        
        friends[a].insert(b);
        
        cout << cnt + compute() << "\n";
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
    
    return 0;
}
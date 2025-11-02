#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, m;
int cnt = 0;

set<int> friends[MAXN];

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b; cin >> a >> b; ++cnt;
        
        friends[a].insert(b);
        
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
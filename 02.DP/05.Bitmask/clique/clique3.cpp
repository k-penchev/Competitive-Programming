#include <bits/stdc++.h>

using namespace std;

const int MAXN = 16;
const int INF = 1e9;

int n, m;
vector<int> g(MAXN), rev_g(MAXN);
int edgesInside[(1 << MAXN)], totalEdges[(1 << MAXN)];
int dp[(1 << MAXN)];

void solve()
{
    cin >> n >> m;

    int x, y;

    for(int i = 0 ; i < m ; ++i)
    {
        cin >> x >> y; --x, --y;

        g[x] |= (1 << y);
        g[y] |= (1 << x);
    }

    for(int i = 0 ; i < n ; ++i)
    {
        int mask = (1 << n) - 1;
        rev_g[i] = (~g[i]) & mask;
        rev_g[i] &= ~(1 << i);
    }

    for(int mask = 0 ; mask < (1 << n) ; ++mask)
    {
        int k = __builtin_popcount(mask);
        totalEdges[mask] = (k * (k - 1)) / 2;
    }

    edgesInside[0] = 0;
    for (int mask = 1; mask < (1 << n); ++mask)
    {
        int node  = __builtin_ctz(mask);            
        edgesInside[mask] = edgesInside[mask ^ (1 << node)] + __builtin_popcount(rev_g[node] & (mask ^ (1 << node)));
    }

    for(int mask = 0 ; mask < (1 << n) ; ++mask)
    {
        dp[mask] = INF;
    }

    dp[0] = 0;
    
    for(int mask = 0 ; mask < (1 << n) ; ++mask)
    {
        for(int submask = mask ; ; submask = (submask - 1) & mask)
        {
            int subset = mask ^ submask;

            int A = subset;
            int B = submask;

            int missing = totalEdges[A] - edgesInside[A];
            int crossing = edgesInside[mask] - edgesInside[A] - edgesInside[B];
        
            dp[mask] = min(dp[mask], missing + crossing + dp[B]);

            if (submask == 0) break;
        }
    }

    cout << dp[(1 << n) - 1] << "\n";
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
}
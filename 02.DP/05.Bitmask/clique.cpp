#include <bits/stdc++.h>

using namespace std;

const int MAXN = 18;
const int INF = 1e9;

int N, M;
vector<int> g(MAXN);
int dp[(1 << MAXN)];

void solve()
{
    cin >> N >> M;

    int x, y;

    for(int i = 0 ; i < M ; ++i)
    {
        cin >> x >> y; --x, --y;

        g[x] |= (1 << y);
        g[y] |= (1 << x);
    }

    
    int fullSetMask = (1 << N) - 1;

    for(int mask = 0 ; mask <= fullSetMask; ++mask)
    {
        dp[mask] = INF;
    }

    bool isClique;

    for(int mask = 0 ; mask <= fullSetMask ; ++mask)
    {
        isClique = true;

        for(int from = 0 ; from < N && isClique ; ++from)
        {
            if(mask & (1 << from))
            {
                if(((g[from] | (1 << from)) & mask) != mask)
                {
                    isClique = false;
                }
            }
        }

        if(isClique)
        {
            dp[mask] = 1;
        }
    }

    for(int mask = 0 ; mask <= fullSetMask ; ++mask)
    {
        for(int submask = mask ; submask != 0 ; submask = (submask - 1) & mask)
        {
            int subset = mask ^ submask;

            int U = submask;
            int V = subset;

            if(dp[U] != INF && dp[V] != INF)
            {
                dp[mask] = min(dp[mask], dp[U] + dp[V]);
            }
        }
    }

    cout << dp[fullSetMask] << "\n";
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
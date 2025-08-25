#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;
const int MOD = 1e9 + 7;

int N, M;
vector<vector<int>> adj(MAXN); // for node I which are its predecessors
int dp[(1 << MAXN)][MAXN];

void solve()
{
    cin >> N >> M;

    int from, to;

    for(int i = 0 ; i < M ; ++i)
    {
        cin >> from >> to; --from, --to;
        adj[to].push_back(from);
    }

    dp[1 << 0][0] = 1;

    int fullSetMask = (1 << N) - 1;

    for(int mask = 2 ; mask <= fullSetMask ; ++mask)
    {
        if((mask & (1 << 0)) == 0) continue;

        if((mask & (1 << (N - 1))) && (mask != fullSetMask)) continue;

        for(int end = 0 ; end < N ; ++end)
        {
            if((mask & (1 << end)) == 0) continue;

            int prev = mask ^ (1 << end);

            for(int predecessor : adj[end])
            {
                if((mask & (1 << predecessor)))
                {
                    dp[mask][end] = (dp[mask][end] + dp[prev][predecessor]) % MOD;
                }
            }
        }
    }

    cout << dp[fullSetMask][N - 1] << "\n";
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
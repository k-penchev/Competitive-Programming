#include <bits/stdc++.h>

using namespace std;

const int MAX = 1e3 + 5;

int n, m, c;
vector<int> cost;
vector<vector<int>> g;
vector<vector<int>> dp;

void solve()
{
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    cin >> n >> m >> c;

    g.resize(n);
    dp.resize(MAX, vector<int>(n, -1));

    for(int i = 0 ; i < n ; ++i)
    {
        int current_cost; cin >> current_cost;
        cost.push_back(current_cost);
    }

    int x, y;

    for(int i = 0 ; i < m ; ++i)
    {
        cin >> x >> y;

        --x, --y;
        
        g[x].push_back(y);
    }

    dp[0][0] = 0;

    for(int time = 0 ; time < MAX ; ++time)
    {
        for(int node = 0 ; node < n ; ++node)
        {
            if (dp[time][node] == -1)
            { 
                continue;
            }

            for(int to : g[node])
            {
                if (time + 1 < MAX) 
                {
                    dp[time + 1][to] = max(dp[time + 1][to], dp[time][node] + cost[to]);
                }
            }
        }
    }

    long long answer = 0;


    for(int time = 0 ; time < MAX ; ++time)
    {
        answer = max(answer, 1LL * dp[time][0] - 1LL * c * time * time);
    }

    cout << answer << "\n";
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
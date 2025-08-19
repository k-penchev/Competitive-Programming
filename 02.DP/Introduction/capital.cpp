#include <bits/stdc++.h>

using namespace std;

typedef long long llong;

const int MAXN = 2 * 1e5 + 10;
const int MAXM = 2 * 1e5 + 10;
const int INF  = 1e9;

int t, n, m;
vector<vector<int>> g(MAXN);
int dist[MAXN];
int sorted[MAXN];
int dp[MAXN];

void bfs(int source)
{
    queue<int> q;

    q.push(source);

    for(int i = 0 ; i < n ; ++i)
    {
        dist[i] = INF;
    }

    dist[source] = 0;

    while(q.size())
    {
        int current_node = q.front();
        q.pop();

        for(int to : g[current_node])
        {
            if(dist[to] == INF)
            {
                dist[to] = dist[current_node] + 1;
                q.push(to);
            }
        }
    }
}

void reset()
{
    memset(sorted, 0, sizeof(sorted));
    memset(dp, 0, sizeof(dp));

    for(auto& ng : g)
    {
        ng.clear();
    }
}

void solve()
{
    cin >> t;

    for(int tt = 0 ; tt < t ; ++tt)
    {
        cin >> n >> m;

        reset();

        int u, v;
        
        for(int j = 0 ; j < m ; ++j)
        {
            cin >> u >> v; --u, --v;
            g[u].push_back(v);
        }

        bfs(0);

        iota(sorted, sorted + n, 0);
        sort(sorted, sorted + n, [&](int x, int y)
        {
            return dist[x] > dist[y];
        });

        cout << "sorted " << "\n";

        for(int i = 0 ; i < n ; ++i)
        {
            cout << sorted[i] + 1 << " ";
        }

        cout << "\n";

        cout << "init dp" << "\n";

        for(int i = 0 ; i < n ; ++i)
        {
            dp[i] = dist[i];
            cout << dp[i] << " ";
        }

        cout << "\n";
        
        for(int i = 0 ; i < n ; ++i)
        {
            int node = sorted[i];

            cout << "node : " << node + 1 << "\n";
            
            for(int to : g[node])
            {

                cout << "to : " << to + 1 << "\n";

                if(dist[node] < dist[to])
                {
                    cout << "->" << "\n";
                    cout << "dp[" << node + 1 << "] = " << dp[node] << " or " << dp[to] << "\n"; 
                    dp[node] = min(dp[node], dp[to]);
                }
                else
                {
                    cout << "--->" << "\n";
                    cout << "dp[" << node + 1 << "] = " << dp[node] << " or " << dist[to] << "\n"; 
                    dp[node] = min(dp[node], dist[to]);
                }   
            }
        }


        cout << "final " << "\n";

        for(int i = 0 ; i < n ; ++i)
        {
            cout << dp[i] << " ";
        }

        cout << "\n";
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
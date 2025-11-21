#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e6 + 10;

int n, m, s, e;
std::vector<int> graph[MAXN];
std::vector<int> rev[MAXN];
std::vector<int> dag[MAXN];
std::vector<int> topo;
bool vis[MAXN];
int component[MAXN];

long long dp[MAXN];
int w[MAXN];
int sum[MAXN];

void dfs1(int node)
{
    vis[node] = true;

    for(int to : graph[node])
    {
        if(!vis[to])
        {
            dfs1(to);
        }
    }

    topo.push_back(node);
}

int sccCount = 0;
void dfs2(int node)
{   
    vis[node] = true;
    component[node] = sccCount; 
    sum[sccCount] += w[node];

    for(int to : rev[node])
    {
        if(!vis[to])
        {
            dfs2(to);
        }
    }
}

void solve()
{
    std::cin >> n >> m >> s >> e;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> w[i];
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;

        graph[a].push_back(b);
        rev[b].push_back(a);
    }

    std::fill(vis + 1, vis + n + 1, false);
    for(int i = 1 ; i <= n ; ++i)
    {
        if(!vis[i])
        {
            dfs1(i);
        }
    }
    
    std::fill(vis + 1, vis + n + 1, false);
    while(!topo.empty())
    {
        int node = topo.back();
        if(!vis[node])
        {
            sccCount += 1;
            dfs2(node);
        }

        topo.pop_back();
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j : graph[i])
        {
            if(component[i] != component[j])
            {
                dag[component[i]].push_back(component[j]);
            }
        }
    }

    std::fill(dp + 1, dp + sccCount + 1, -1e18);
    dp[component[e]] = 0;

    for(int i = sccCount ; i >= 1 ; --i)
    {
        for(int j : dag[i])
        {
            dp[i] = std::max(dp[i], dp[j]);
        }

        dp[i] += sum[i];
    }

    std::cout << dp[component[s]] << "\n";
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
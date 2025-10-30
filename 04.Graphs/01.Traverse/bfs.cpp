#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int MAXN = 1e5 + 10;

int n, m;
std::vector<int> g[MAXN];
bool vis[MAXN];

void bfs(int source)
{
    std::queue<int> q;
    
    q.push(source);
    vis[source] = 1;

    while(q.size())
    {
        int u = q.front();
        q.pop();

        for(int v : g[u])
        {
            if(!vis[v])
            {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;

        g[a].push_back(b);
        g[b].push_back(a);
    }

    bfs(1);
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
    
    return 0;
}
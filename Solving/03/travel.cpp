#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int MAXN = 1e5;
const int INF = 1e9;

int n;
int radius[MAXN];
std::vector<int> tree[MAXN], g[MAXN];
int vis[MAXN], dist[MAXN];

void bfs(int source)
{
    std::fill(dist + 1, dist + n + 1, INF);
    std::queue<int> q;

    dist[source] = 0;
    vis[source] = 1;
    q.push(source);

    while(q.size())
    {
        int curr = q.front();
        q.pop();

        for(const int& to : g[curr])
        {
            if(vis[to]) continue;
            vis[to] = 1;
            
            dist[to] = std::min(dist[to], dist[curr] + 1);
            q.push(to);
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(dist[i] == INF) std::cout << "-1" << " ";
        else std::cout << dist[i] << " ";
    }

    std::cout << "\n";
}

void dfs(int node, int par, int curr_d, int root, int max_d)
{
    if(curr_d > max_d) return;

    if(curr_d == max_d)
    {
        g[root].push_back(node);
    }

    for(const int& to : tree[node])
    {
        if(to == par) continue;
        dfs(to, node, curr_d + 1, root, max_d);
    }
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> radius[i];
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        std::cin >> a >> b; ++a, ++b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        dfs(i, 0, 0, i, radius[i]);
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
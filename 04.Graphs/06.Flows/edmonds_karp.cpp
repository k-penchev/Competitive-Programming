//second
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int MAXN = 2e2 + 10;
const int INF = 1e9 + 10;

int t, n;

struct Edge
{
    int to;
    int flow;
    int capacity;
    int backEdge;
};

std::vector<Edge> g[MAXN];
int dist[MAXN];
std::queue<int> q;
int source, sink;

bool bfs()
{
    std::fill(dist + 1, dist + n + 1, INF);
    
    dist[source] = 0;
    q.push(source);

    while(q.size())
    {
        int node = q.front();
        q.pop();

        for(auto &[to, flow, cap, backEdge] : g[node])
        {
            if(flow == cap)
            {
                continue;
            }

            if(dist[to] == INF)
            {
                dist[to] = dist[node] + 1;
                q.push(to);
            }
        }
    }

    return dist[sink] != INF;
}

int dfs(int node, int incomingFlow)
{
    if(node == sink)
    {
        return incomingFlow;
    }

    for(int i = 0 ; i < g[node].size() ; ++i)
    {
        auto &[to, flow, cap, backEdge] = g[node][i];

        if(flow == cap || dist[to] != dist[node] + 1)
        {
            continue;
        }

        int res = dfs(to, std::min(incomingFlow, cap - flow));
        if(res > 0)
        {
            flow += res;
            g[to][backEdge].flow -= res;
            return res;
        }
    }

    return 0;
}

int edmonds_karp()
{
    int ans = 0;

    while(bfs())
    {
        ans += dfs(source, INF);
    }

    return ans;
}

void addEdge(int u, int v, int cap)
{
    g[u].push_back({v, 0, cap, (int)g[v].size()});
    g[v].push_back({u, 0, 0, (int)g[u].size() - 1});
}

void solve()
{
    std::cin >> n;
    source = 1; sink = n;
    
    for(int u = 1 ; u <= n - 1; ++u)
    {
        int cnt; std::cin >> cnt;
        for(int k = 1 ; k <= cnt ; ++k)
        {
            int v; std::cin >> v;
            
            if(u == source || v == sink) addEdge(u, v, 1);
            else addEdge(u, v, INF);
        }
    }

    std::cout << edmonds_karp() << "\n";
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
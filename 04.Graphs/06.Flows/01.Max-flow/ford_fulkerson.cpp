//first
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 2e2 + 10;
const int INF = 1e9 + 10;

int n;

struct Edge
{
    int to;
    int flow;
    int capacity;
    int backEdge;
};

std::vector<Edge> g[MAXN];
bool visited[MAXN];
int source, sink;

int dfs(int node, int incomingFlow)
{
    visited[node] = 1;

    if(node == sink)
    {
        return incomingFlow;
    }

    for(int i = 0 ; i < g[node].size() ; ++i)
    {
        auto &[to, flow, cap, backEdge] = g[node][i];

        if(visited[to] || flow == cap)
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

int ford_fulkerson()
{
    int ans = 0;

    while(true)
    {
        std::fill(visited + 1, visited + n + 1, false);
        int incomingFlow = dfs(source, INF);

        if(incomingFlow == 0)
        {
            break;
        }

        ans += incomingFlow;
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

    std::cout << ford_fulkerson() << "\n";
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
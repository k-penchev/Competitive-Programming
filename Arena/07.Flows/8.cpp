#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>

const int MAXN = 100 + 1;
const int INF = 1e9;

int n, m, q;

struct Edge
{
    int to;
    int flow;
    int cap;
    int rev;
};

std::vector<Edge> g[MAXN];
int dist[MAXN], ptr[MAXN];
int source, sink;

bool bfs()
{
    std::fill(dist + 1, dist + n + 1, INF);
    std::queue<int> q;

    dist[source] = 0;
    q.push(source);

    while(q.size())
    {
        int node = q.front();
        q.pop();

        for(auto &[to, flow, cap, rev] : g[node])
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

    for(int &i = ptr[node] ; i < g[node].size() ; ++i)
    {
        auto &[to, flow, cap, rev] = g[node][i];

        if(dist[node] + 1 != dist[to] || flow == cap)
        {
            continue;
        }

        int res = dfs(to, std::min(incomingFlow, cap - flow));
        if(res > 0)
        {
            flow += res;
            g[to][rev].flow -= res;
            return res;
        }
    }

    return 0;
}

int dinic()
{
    int answer = 0;

    while(bfs())
    {
        std::fill(ptr + 1, ptr + n + 1, 0);

        int current;
        do
        {
            current = dfs(source, INF);
            
            answer += current;
            if(current == 0) break;
        }
        while(true);
    }

    return answer;
}

void addEdge(int from, int to, int cap)
{
    g[from].push_back({to, 0, cap, (int)g[to].size()});
    g[to].push_back({from, 0, 0, (int)g[from].size() - 1});
}

void solve()
{
    std::cin >> n >> m;
    
    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        addEdge(a, b, 1);
        addEdge(b, a, 1);
    }

    source = 1, sink = n;

    int answer = dinic();
    std::cout << answer << "\n";

    std::cin >> q;
    for(int i = 1 ; i <= q ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        
        addEdge(a, b, 1);
        addEdge(b, a, 1);
        
        answer += dinic();
        std::cout << answer << "\n";
    }
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
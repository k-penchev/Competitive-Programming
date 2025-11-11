//Minimum cut is equal to maximum flow
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

const int MAXN = 2e2 + 10;
const int INF = 1e9;

int n, m;

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

bool visited[MAXN];
bool inSourceSide[MAXN];

std::vector<int> left;
std::vector<int> right;

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

        if(flow == cap || dist[node] + 1 != dist[to])
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
        }
        while(current != 0);
    }

    return answer;
}

void findMinCut(int node)
{
    visited[node] = 1;
    inSourceSide[node] = 1;

    for(auto &[to, flow, cap, rev] : g[node])
    {
        if(flow == cap)
        {
            continue;
        }

        if(!visited[to])
        {
            findMinCut(to);
        }
    }
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
        int a, b, c;
        std::cin >> a >> b >> c;
        addEdge(a, b, c);
    }

    source = 1, sink = n;

    //find maximum flow (minimum cut)
    dinic();

    //get the nodes
    findMinCut(source);

    for(int i = 1 ; i <= n ; ++i)
    {
        if(inSourceSide[i])
        {
            left.push_back(i);
        }
        else
        {
            right.push_back(i);
        }
    }
}

void output()
{
    std::cout << "\n";
    for(int node : left)
    {
        std::cout << node << " ";
    }

    std::cout << "\n";
    for(int node : right)
    {
        std::cout << node << " ";
    }

    std::cout << "\n";
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
    output();
    
    return 0;
}
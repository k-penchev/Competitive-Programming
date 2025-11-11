#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

const int MAXN = 1000 + 10;
const int MAX_NODES = 10 * MAXN;
const int INF = 1e9 + 10;

int n, k;
bool banned[MAXN][MAXN];
int rowID[MAXN][MAXN];
int colID[MAXN][MAXN];
int globalID = 2; //1 is for the super source

struct Edge
{
    int to;
    int flow;
    int cap;
    int rev;
};

int nodes;
std::vector<Edge> g[MAX_NODES];
std::vector<int> sources;
std::vector<int> sinks;
int source, sink;

int dist[MAX_NODES], ptr[MAX_NODES];

struct Rook
{
    int x;
    int y;
};

std::vector<Rook> answer;
std::unordered_map<long long, int> edges;

void calcRooks()
{
    for(int &leaf : sources)
    {
        for(auto &[to, flow, cap, rev] : g[leaf])
        {
            if(flow == 1 && cap == 1)
            {
                long long key = (1LL * leaf << 32) ^ to;
                edges[key] = 1;
            }
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            if(banned[i][j])
            {
                continue;
            }

            long long key = (1LL * rowID[i][j] << 32) ^ colID[i][j];
            auto it = edges.find(key);

            if(it != edges.end())
            {
                answer.push_back({i, j});
                edges.erase(it);
            }
        }
    }
}

bool bfs()
{
    std::fill(dist + 1, dist + nodes + 1, INF);
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

void dinic()
{
    int answer = 0;

    while(bfs())
    {
        std::fill(ptr + 1, ptr + nodes + 1, 0);

        int current;
        do 
        {
            current = dfs(source, INF);
            answer += current;
        }
        while(current > 0);
    }
}

void addEdge(int from, int to, int cap)
{
    g[from].push_back({to, 0, cap, (int)g[to].size()});
    g[to].push_back({from, 0, 0, (int)g[from].size() - 1});
}

void solve()
{
    std::cin >> n >> k;

    for(int i = 1 ; i <= k ; ++i)
    {
        int x, y;
        std::cin >> x >> y;
        banned[x][y] = 1;
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            if(banned[i][j])
            {
                continue;
            }

            if(j == 1 || banned[i][j - 1])
            {
                globalID += 1;
                sources.push_back(globalID);
            }

            rowID[i][j] = globalID;
        }
    }

    for(int j = 1 ; j <= n ; ++j)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            if(banned[i][j])
            {
                continue;
            }

            if(i == 1 || banned[i - 1][j])
            {
                globalID += 1;
                sinks.push_back(globalID);
            }

            colID[i][j] = globalID;
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            if(banned[i][j])
            {
                continue;
            }

            addEdge(rowID[i][j], colID[i][j], 1);
        }
    }

    source = 1, sink = nodes = globalID + 1;
    
    for(int &leaf : sources)
    {
        addEdge(source, leaf, 1);
    }

    for(int &leaf : sinks)
    {
        addEdge(leaf, sink, 1);
    }

    dinic();
    calcRooks();

    std::cout << answer.size() << "\n";

    for(auto &[x, y] : answer)
    {
        std::cout << x << "  "  << y << "\n";
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
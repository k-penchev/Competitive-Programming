#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define int long long

const int MAXN = 30 + 1;
const int MAXV = 1e4 + 10;
const int INF = 1e9;

int n, m;
char table[MAXN][MAXN];
int inID[MAXN][MAXN], outID[MAXN][MAXN];
int globalID = 0;

struct Edge
{
    int to;
    int flow;
    int cap;
    int rev;
};

int nodes;
std::vector<Edge> g[MAXV];

std::vector<int> sources;
std::vector<int> sinks;
int multiSource, multiSink;

int dist[MAXV], ptr[MAXV];

int dfs(int node, int incomingFlow)
{
    if(node == multiSink)
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

bool bfs()
{
    std::fill(dist + 1, dist + nodes + 1, INF);
    std::queue<int> q;

    dist[multiSource] = 0;
    q.push(multiSource);

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

    return dist[multiSink] != INF;
}

int dinic()
{
    int answer = 0;

    while(bfs())
    {
        std::fill(ptr + 1, ptr + nodes + 1, 0);

        int current;
        do
        {
            current = dfs(multiSource, INF);
            answer += current;

            if(current == 0) break;
        }
        while(true);
    }

    return answer;
}

void addEdge(int from, int to)
{
    g[from].push_back({to, 0, 1, (int)g[to].size()});
    g[to].push_back({from, 0, 0, (int)g[from].size() - 1});
}

void build(int i, int j)
{
    if(i - 1 >= 1)
    {
        addEdge(outID[i][j], inID[i - 1][j]);
    }

    if(i + 1 <= n)
    {
        addEdge(outID[i][j], inID[i + 1][j]);
    }

    if(j - 1 >= 1)
    {
        addEdge(outID[i][j], inID[i][j - 1]);
    }

    if(j + 1 <= m)
    {
        addEdge(outID[i][j], inID[i][j + 1]);
    }
}

int nextID()
{
    globalID += 1;
    return globalID;
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::string s;
        std::cin >> s;
        
        m = s.size();
        for(int j = 0 ; j < m ; ++j)
        {
            table[i][j + 1] = s[j];
            inID[i][j + 1] = nextID();
            outID[i][j + 1] = nextID();
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= m ; ++j)
        {
            addEdge(inID[i][j], outID[i][j]);
            build(i, j);

            if(table[i][j] == '1')
            {
                sources.push_back(inID[i][j]);
            }

            if(i == 1 || i == n || j == 1 || j == m)
            {
                sinks.push_back(outID[i][j]);
            }
        }
    }

    multiSource = nextID();
    multiSink = nextID();

    for(int &s : sources)
    {
        addEdge(multiSource, s);
    }

    for(int &s : sinks)
    {
        addEdge(s, multiSink);
    }

    nodes = 1e4;
    std::cout << dinic() << "\n";
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int MAXN = 200 + 5;
const int MAX_SUM = 2 * 500 + 5;
const int INF = 1e9 + 10;

int n;
int a[MAXN];
bool isPrime[MAX_SUM];
std::vector<int> even;
std::vector<int> odd;
int cntOnes = 0;

struct Edge
{
    int to;
    int flow;
    int cap;
    int rev;
};

int nodes;
std::vector<Edge> g[MAXN];
std::vector<int> sources;
std::vector<int> sinks;
int source, sink;

int dist[MAXN], ptr[MAXN];

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

int dinic()
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

    return answer;
}

void addEdge(int from, int to, int cap)
{
    g[from].push_back({to, 0, cap, (int)g[to].size()});
    g[to].push_back({from, 0, 0, (int)g[from].size() - 1});
}

void sieve()
{
    std::fill(isPrime, isPrime + MAX_SUM, true);

    for(int i = 2 ; i * i < MAX_SUM ; ++i)
    {
        if(isPrime[i])
        {
            for(int j = i * i ; j < MAX_SUM ; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    sieve();

    for(int i = 1 ; i <= n ; ++i)
    {
        if(a[i] % 2 == 0)
        {
            even.push_back(i);
            sources.push_back(i);
        }
        else
        {
            odd.push_back(i);
            sinks.push_back(i);
        }

        if(a[i] == 1)
        {
            cntOnes += 1;
        }
    }

    for(int &evenIdx : even)
    {
        for(int &oddIdx : odd)
        {
            if(isPrime[a[evenIdx] + a[oddIdx]])
            {
                addEdge(evenIdx, oddIdx, 1);
            }
        }
    }

    source = n + 1, sink = nodes = n + 2;
    
    for(int &leaf : sources)
    {
        addEdge(source, leaf, 1);
    }

    for(int &leaf : sinks)
    {
        addEdge(leaf, sink, 1);
    }

    std::cout << dinic() + cntOnes * (cntOnes - 1) / 2 << "\n";
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
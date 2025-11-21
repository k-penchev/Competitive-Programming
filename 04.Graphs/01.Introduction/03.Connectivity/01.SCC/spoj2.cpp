#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, m;
std::vector<int> graph[MAXN];
std::vector<int> rev[MAXN];
std::vector<int> condensed[MAXN];
std::vector<int> topo;
bool vis[MAXN];
int outDeg[MAXN];
int component[MAXN];

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
    condensed[sccCount].push_back(node);

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
    std::cin >> n >> m;

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
                outDeg[component[i]] += 1;
            }
        }
    }

    int idx = -1, cnt = 0;
    for(int i = 1 ; i <= sccCount ; ++i)
    {
        if(outDeg[i] == 0)
        {
            idx = i;
            cnt += 1;
        }
    }

    if(cnt > 1)
    {
        std::cout << "0\n";
        exit(0);
    }

    std::sort(condensed[idx].begin(), condensed[idx].end());

    std::cout << condensed[idx].size() << "\n";
    for(int x : condensed[idx]) std::cout << x << " ";
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
}
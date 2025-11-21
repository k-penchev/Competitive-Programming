//https://en.wikipedia.org/wiki/Strong_connectivity_augmentation
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1600 + 10;

int n, m;
std::vector<int> g[MAXN];
std::vector<int> rev[MAXN];
std::vector<int> order;

bool vis[MAXN];
int component[MAXN];
int inDegree[MAXN];
int outDegree[MAXN];

int first, second;

void dfs1(int node)
{
    vis[node] = 1;
    
    for(int &to : g[node])
    {
        if(!vis[to])
        {
            dfs1(to);
        }
    }

    order.push_back(node);
}

int sccCount = 0;
void dfs2(int node)
{
    vis[node] = 1;
    component[node] = sccCount;

    for(int &to : rev[node])
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
        a += 1, b += 1;
        g[a].push_back(b);
        rev[b].push_back(a);
    }

    std::fill(vis + 1, vis + n + 1, 0); 
    for(int i = 1 ; i <= n ; ++i)
    {
        if(!vis[i])
        {
            dfs1(i);
        }
    }

    std::fill(vis + 1, vis + n + 1, 0);
    while(order.size())
    {
        int node = order.back();

        if(!vis[node])
        {
            sccCount += 1;
            dfs2(node);
        }

        order.pop_back();
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int &j : g[i])
        {
            if(component[i] == component[j]) continue;
            outDegree[component[i]] += 1;
            inDegree[component[j]] += 1;
        }
    }

    
    for(int i = 1 ; i <= sccCount ; ++i)
    {
        if(inDegree[i] == 0) first += 1;
        if(outDegree[i] == 0) second += 1;
    }

    std::cout << first << " ";

    if(sccCount == 1) first = second = 0;
    std::cout << std::max(first, second) << "\n";
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
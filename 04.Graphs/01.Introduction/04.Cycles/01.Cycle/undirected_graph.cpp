#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, m;
std::vector<int> g[MAXN];
bool visited[MAXN];
int parent[MAXN];
int startNode, endNode; // [start, end] of a cycle

bool dfs(int node, int par)
{
    visited[node] = 1;

    for(int to : g[node])
    {
        if(to == par)
        {
            continue;
        }

        if(visited[to])
        {
            startNode = to;
            endNode = node;
            return true;
        }
        
        parent[to] = node;
        if(dfs(to, node))
        {
            return true;
        }
    }

    return false;
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int hasCycle = false;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(!visited[i])
        {
            if(dfs(i, -1))
            {
                hasCycle = true;
                break;
            }
        }
    }

    if(!hasCycle)
    {
        std::cout << "Cycle not found." << "\n";
        return;
    }

    std::vector<int> cycle;
    for(int node = endNode ; node != startNode ; node = parent[node])
    {
        cycle.push_back(node);
    }

    cycle.push_back(startNode);
    std::reverse(cycle.begin(), cycle.end());

    //optional
    cycle.push_back(startNode);

    std::cout << cycle.size() << "\n";
    for(int &x : cycle)
    {
        std::cout << x << " ";
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
    
    return 0;
}
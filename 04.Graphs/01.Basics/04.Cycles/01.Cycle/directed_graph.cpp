#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, m;
std::vector<int> g[MAXN];
int color[MAXN]; //white(unvisited), gray(visited and unfinished), black(visited and finished) 
int parent[MAXN];
int startNode, endNode; // [start, end] of a cycle

bool dfs(int node)
{
    color[node] = 1;

    for(int to : g[node])
    {
        if(color[to] == 0)
        {
            parent[to] = node;
            if(dfs(to))
            {
                return true;
            }
        }
        else if(color[to] == 1)
        {
            startNode = to;
            endNode = node;
            return true;
        }
    }

    color[node] = 2;
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
    }

    int hasCycle = false;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(color[i] == 0)
        {
            if(dfs(i))
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
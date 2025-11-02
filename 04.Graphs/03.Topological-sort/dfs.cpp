#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, m;
std::vector<int> g[MAXN];
std::vector<int> stack; //topo sort
bool vis[MAXN];
int byIndex[MAXN];

void dfs(int node)
{
    vis[node] = 1;

    for(int to : g[node])
    {
        if(!vis[to])
        {
            dfs(to);
        }
    }
    
    stack.push_back(node);
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

    for(int i = 1 ; i <= n ; ++i)
    {
        if(!vis[i])
        {
            dfs(i);
        }
    }

    std::reverse(stack.begin(), stack.end());

    int cnt = 1;
    for(int x : stack)
    {
        byIndex[x] = cnt++;
    }

    for(int x = 1 ; x <= n ; ++x)
    {
        for(int y : g[x])
        {
            if(byIndex[x] >= byIndex[y])
            {
                std::cout << "IMPOSSIBLE" << "\n";
                exit(0);
            }
        }
    }

    for(int x : stack)
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
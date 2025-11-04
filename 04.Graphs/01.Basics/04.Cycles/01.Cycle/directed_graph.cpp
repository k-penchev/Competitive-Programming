#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, m;
std::vector<int> g[MAXN];
int color[MAXN]; //white(unvisited), gray(visited and unfinished), black(visited and finished) 
int parent[MAXN];
int startNode, endNode; // [start, end] of a cycle

bool dfs(int node, int parent)
{

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

    std::cout << dfs(1, -1) << "\n";
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
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

const int MAXN = 5 * 1e5 + 5;

int n, m;
std::vector<int> g[MAXN];
int root;
std::vector<int> tour, leaves;
bool isLeaf[MAXN];

void dfs(int node, int par)
{
    tour.push_back(node);
    isLeaf[node] = true;

    for(int to : g[node])
    {
        if(to == par) continue;
        isLeaf[node] = false;
        dfs(to, node);
    }
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

    for(int i = 1 ; i <= n ; ++i) 
    {
        if(g[i].size() > 1)
        {
            root = i;
            break;
        }
    }

    dfs(root, -1);

    for(int x : tour)
    {
        if(isLeaf[x]) leaves.push_back(x);
    }

    int T = leaves.size();
    int H = std::ceil(T / 2.0);

    std::cout << H << "\n";
    for(int i = 0 ; i < H ; ++i)
    {
        std::cout << leaves[i] << " " << leaves[(i + H) % T] << "\n";
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
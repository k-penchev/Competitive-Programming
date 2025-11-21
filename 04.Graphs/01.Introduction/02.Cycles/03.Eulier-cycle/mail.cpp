#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int MAXM = 2 * 1e5 + 10;

int n, m;

struct Edge
{
    int to;
    int idx;
};

std::vector<Edge> g[MAXN];
std::vector<int> cycle;

int deg[MAXN];
bool visited[MAXM];

void euler(int node)
{
    while(!g[node].empty())
    {
        auto [to, idx] = g[node].back();
        g[node].pop_back();

        if(visited[idx])
        {
            continue;
        }

        visited[idx] = 1;
        euler(to);
    }

    cycle.push_back(node);
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});

        deg[a] += 1; deg[b] += 1;
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(deg[i] % 2 != 0)
        {
            std::cout << "IMPOSSIBLE" << "\n";
            exit(0);
        }
    }

    euler(1);

    if(cycle.size() != m + 1)
    {
        std::cout << "IMPOSSIBLE" << "\n";
        exit(0);
    }
    
    std::reverse(cycle.begin(), cycle.end());
    for(int i = 0 ; i < cycle.size() ; ++i)
    {
        std::cout << cycle[i] << " ";
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
}
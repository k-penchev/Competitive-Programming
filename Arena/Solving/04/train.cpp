#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 1e5 + 10;
const int MAXM = 2 * 1e6 + 10;

int n, m;

struct Edge
{
    int to;
    int idx;
};

std::vector<Edge> g[MAXN];
std::vector<int> cycle;

bool vis[MAXM];

void euler(int node, int edge)
{
    while(g[node].size())
    {
        auto [to, idx] = g[node].back();
        g[node].pop_back();

        if(vis[idx]) continue;

        vis[idx] = 1;
        euler(to, idx);
    }

    cycle.push_back(edge);
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        assert(c == 2);

        g[a].push_back({b, i});
        g[a].push_back({b, i});

        g[b].push_back({a, i + m});
        g[b].push_back({a, i + m});
    }


    euler(1, 0);
    cycle.pop_back();

    std::cout << cycle.size() << "\n";
    for(int x : cycle)
    {
        if(x <= m) std::cout << x << " ";
        else std::cout << x - m << " ";
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
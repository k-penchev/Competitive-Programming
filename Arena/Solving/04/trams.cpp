#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <map>

const int MAXN = 50000 + 10;
const int MAXM = 5 * 100000 + 10;

int n, m;

struct Edge
{
    int to;
    int idx;
};

std::vector<Edge> g[MAXN];
std::map<std::pair<int, int>, int> map;
std::vector<std::pair<int, int>> cycle;
std::vector<int> paths[MAXN];

int deg[MAXN];
bool visited[MAXM];

void euler(int node, int edge)
{
    while(g[node].size())
    {
        auto [to, idx] = g[node].back();
        g[node].pop_back();

        if(visited[idx])
        {
            continue;
        }

        visited[idx] = 1;
        euler(to, idx);
    }

    cycle.push_back({node, edge});
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
        deg[a] += 1, deg[b] += 1;
    }

    std::vector<int> odd;

    for(int i = 1 ; i <= n ; ++i)
    {
        if(deg[i] % 2 == 1)
        {
            odd.push_back(i);
        }
    }

    assert(odd.size() % 2 == 0);
    for(int i = 0, idx = m + 1 ; i < odd.size() ; i += 2, idx += 1)
    {
        g[odd[i]].push_back({odd[i + 1], idx});
        g[odd[i + 1]].push_back({odd[i], idx});
    }

    euler(1, 0);

    int cnt = 1;
    while(!cycle.empty())
    {
        if(cycle.back().second > m) cnt += 1;

        paths[cnt].push_back(cycle.back().first);
        cycle.pop_back();
    }

    if(cnt > 1)
    {
        for(int i = 1 ; i < paths[1].size() ; ++i)
        {
            paths[cnt].push_back(paths[1][i]);
        }

        paths[1] = paths[cnt];
        cnt -= 1;
    }

    std::cout << cnt << "\n";

    for(int i = 1 ; i <= cnt ; ++i)
    {
        std::cout << paths[i].size() << " ";

        for(int x : paths[i]) std::cout << x << " ";
        std::cout << "\n";
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
}
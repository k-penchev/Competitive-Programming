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
std::vector<int> path;

int in[MAXN], out[MAXN];
bool visited[MAXM];

void euler(int node)
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
        euler(to);
    }

    path.push_back(node);
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;

        g[a].push_back({b, i});
        out[a] += 1, in[b] += 1;
    }

    in[1] += 1, out[n] += 1;

    for(int i = 1 ; i <= n ; ++i)
    {
        if(in[i] != out[i])
        {
            std::cout << "IMPOSSIBLE" << "\n";
            exit(0);
        }
    }

    euler(1);

    if(path.size() != m + 1)
    {
        std::cout << "IMPOSSIBLE" << "\n";
        exit(0);
    }

    std::reverse(path.begin(), path.end());
    for(int x : path)
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
}
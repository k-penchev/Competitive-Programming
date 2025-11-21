#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

const int MAXN = 200 + 10;
const int MAXM = 1000 + 10;

int n, m;

struct Edge
{
    int to;
    int idx;
};

std::vector<Edge> g[MAXN];
int degree[MAXN];
bool visited[MAXM];
std::stack<int> euler;

void dfsFast(int node) // O (N)
{
    while(g[node].size())
    {
        auto [to, idx] = g[node].back();
        g[node].pop_back();

        if(visited[idx])
        {
            continue;
        }

        visited[idx] = true;
        dfsFast(to);
    }

    euler.push(node);
}

void dfsSlow(int node) // O (N ^ 2)
{
    for(int i = 0 ; i < g[node].size() ; ++i)
    {
        auto [to, idx] = g[node][i];

        if(visited[idx])
        {
            continue;
        }

        visited[idx] = true;
        dfsSlow(to);
    }

    euler.push(node);
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

        degree[a] += 1;
        degree[b] += 1;
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(degree[i] % 2 != 0)
        {
            std::cout << "Not found." << "\n";
            exit(0);
        }
    }

    dfsFast(1);

    std::cout << "Found." << "\n";
    while(euler.size())
    {
        std::cout << euler.top() << " ";
        euler.pop();
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
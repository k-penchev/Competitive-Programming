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
int in[MAXN], out[MAXN];
bool visited[MAXM];
std::stack<int> euler;

void dfs(int node) 
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
        dfs(to);
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

        out[a] += 1;
        in[b] += 1;
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(in[i] != out[i])
        {
            std::cout << "Not found." << "\n";
            exit(0);
        }
    }

    dfs(1);

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
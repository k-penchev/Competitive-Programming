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
        g[b].push_back({a, i});
        
        degree[a] += 1;
        degree[b] += 1;
    }

    int start = -1;
    int odd = 0;

    for(int i = 1; i <= n; ++i)
    {
        if(degree[i] % 2 == 1)
        {
            odd++;
            start = i;   
        }

        if(degree[i] > 0 && start == -1)
        {
            start = i;         
        }
    }

    if(!(odd == 0 || odd == 2))
    {
        std::cout << "Not found." << "\n";
        exit(0);
    }

    dfs(start);

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
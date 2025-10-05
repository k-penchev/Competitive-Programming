#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

#define int long long

const int MAXN = 1e5 + 5;

int n, m;
std::vector<int> g[MAXN], rev_g[MAXN];
std::stack<int> order;
int component[MAXN];
bool vis[MAXN];

std::vector<int> dag[MAXN];
std::vector<int> topo;
int w[MAXN], dp[MAXN];
int answer = 0;

void dfs1(int node)
{
    vis[node] = true;

    for(int to : g[node])
    {
        if(!vis[to])
        {
            dfs1(to);
        }
    }

    order.push(node);
}

void dfs2(int node, int id)
{
    component[node] = id;
    w[id] += 1;

    for(int to : rev_g[node])
    {
        if(component[to] == -1)
        {
            dfs2(to, id);
        }
    }
}

void dfs3(int node)
{
    vis[node] = true;

    for(int to : dag[node])
    {
        if(!vis[to])
        {
            dfs3(to);
        }
    }

    order.push(node);
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
            dfs1(i);
        }
    }
        
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int x : g[i])
        {
            rev_g[x].push_back(i);
        }
    }

    std::fill(component + 1, component + n + 1, -1);

    int cnt = 1;
    while(!order.empty())
    {
        int node = order.top();
        order.pop();

        if(component[node] == -1)
        {
            dfs2(node, cnt++);
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j : g[i])
        {
            if(component[i] != component[j])
            {
                dag[component[i]].push_back(component[j]);
                //std:: cout << component[i] << " --> " << component[j] << "\n";
            }
        }
    }

    while(!order.empty()) order.pop();
    std::fill(vis + 1, vis + n + 1, 0);
    for(int i = 1 ; i <= cnt ; ++i)
    {
        if(!vis[i])
        {
            dfs3(i);
        }
    }

    while(!order.empty())
    {
        topo.push_back(order.top());
        order.pop();
    }

    std::reverse(topo.begin(), topo.end());
    for(int i : topo)
    {
        int best = 0;
        for(int j : dag[i])
        {
            best = std::max(best, dp[j]);
        }

        dp[i] = w[i] + best;
        answer = std::max(answer, dp[i]);
    }

    std::cout << answer << "\n";
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
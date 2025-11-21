#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 100 + 10;

int t, n;
std::vector<int> g[MAXN];
std::vector<int> rev[MAXN];
std::vector<int> order;
bool vis[MAXN];

void dfs1(int node)
{
    vis[node] = 1;
    for(int to : g[node])
    {
        if(!vis[to])
        {
            dfs1(to);
        }
    }

    order.push_back(node);
}

void dfs2(int node)
{
    vis[node] = 1;
    //comp[node] = id;

    for(int to : rev[node])
    {
        if(!vis[to])
        {
            dfs2(to);
        }
    }
}

void reset()
{
    order.clear();

    for(auto &adj : g)
    {
        adj.clear();
    }

    for(auto &adj : rev)
    {
        adj.clear();
    }
}

void solve()
{
    std::cin >> t;
    for(int tt = 1 ; tt <= t ; ++tt)
    {
        std::cin >> n;
        for(int i = 1 ; i <= n ; ++i)
        {
            for(int j = 1 ; j <= n ; ++j)
            {
                char c;
                std::cin >> c;

                if(c == 'Y')
                {
                    g[i].push_back(j);
                    rev[j].push_back(i);
                }
            }
        }

        std::fill(vis + 1, vis + n + 1, false);
        for(int i = 1 ; i <= n ; ++i)
        {
            if(!vis[i])
            {
                dfs1(i);
            }
        }

        int counter = 0;
        std::fill(vis + 1, vis + n + 1, false);
        while(!order.empty())
        {
            int node = order.back();
            if(!vis[node])
            {
                dfs2(node);
                counter += 1;
            }

            order.pop_back();
        }

        std::cout << counter << "\n";
        reset();
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
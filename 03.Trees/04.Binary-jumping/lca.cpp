#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 200000 + 10;
const int INF = 1e9 + 10;
const int MAXLOG = 20;

int n, q;
std::vector<int> tree[MAXN];
int parent[MAXN][MAXLOG];
int in[MAXN];
int out[MAXN];
int timer;

bool isAnsector(int u, int v)
{
    return (in[u] <= in[v] && out[u] >= out[v]);
}

int query(int u, int v)
{
    if(isAnsector(u, v))
    {
        return u;
    }

    if(isAnsector(v, u))
    {
        return v;
    }

    for(int lg = MAXLOG - 1 ; lg >= 0 ; --lg)
    {
        int next = parent[u][lg];

        if(next != 0 && !isAnsector(next, v))
        {
            u = next;
        }
    }

    return parent[u][0];
}

void euler(int node, int par)
{
    in[node] = ++timer;
    for(int lg = 0 ; lg < MAXLOG ; ++lg)
    {
        if(lg == 0)
        {
            parent[node][lg] = par;
            continue;
        }
        parent[node][lg] = parent[parent[node][lg - 1]][lg - 1];
    }

    for(const int &to : tree[node])
    {
        euler(to, node);
    }
    out[node] = timer;
}

void solve()
{
    std::cin >> n >> q;
    for(int i = 2 ; i <= n ; ++i)
    {
        int par;
        std::cin >> par;
        tree[par].push_back(i);
    }

    euler(1, 0);
    for(int i = 1 ; i <= q ; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        std::cout << query(u, v) << "\n";
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
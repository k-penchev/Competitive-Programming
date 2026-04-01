#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 200000 + 10;
const int MAXLOG = 20;

int n, q;
std::vector<int> tree[MAXN];
int parent[MAXN][MAXLOG];

int query(int x, int kth)
{
    int node = x;
    for(int lg = 0 ; lg < MAXLOG ; ++lg)
    {
        if(kth & (1 << lg))
        {
            node = parent[node][lg];
            if(node == 0) break;
        }
    }

    return (node != 0 ? node : -1);
}

void dfs(int node, int par)
{
    for(int lg = 0 ; lg < MAXLOG ; ++lg)
    {
        if(lg == 0)
        {
            parent[node][lg] = par;
            continue;
        }

        int prev = parent[node][lg - 1];
        parent[node][lg] = parent[prev][lg - 1];
    }

    for(const int &to : tree[node])
    {
        dfs(to, node);
    }
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

    dfs(1, 0);
    for(int i = 1 ; i <= q ; ++i)
    {
        int node, kth;
        std::cin >> node >> kth;
        std::cout << query(node, kth) << "\n";
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
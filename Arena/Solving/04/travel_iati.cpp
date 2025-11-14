#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int MAXN = 1e5 + 10;

int n, m;
std::queue<int> g[MAXN];
std::vector<int> friends;
int ptr = 0;
long long ans = 0;

void dfs(int node)
{
    //std::cout << node << " ";

    if(ptr == m)
    {
        return;
    }

    if(node == friends[ptr])
    {
        ptr += 1;
    }

    int to = g[node].front();
    g[node].pop();
    g[node].push(to);

    ans += 1;
    dfs(to);
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
    {
        int k;
        std::cin >> k;

        for(int j = 1 ; j <= k ; ++j)
        {
            int x;
            std::cin >> x;
            g[i].push(x);
        }
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int f;
        std::cin >> f;
        friends.push_back(f);
    }

    dfs(1);
    std::cout << ans << "\n";
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
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 80 + 5;
const int MAXM = 500 + 5;
const int INF = 1e9 + 10;

int n, m;
bool toll[MAXN];

struct Edge
{
    int to;
    int w;
    int tollCnt;
};

std::vector<Edge> g[MAXN];

void bellman_ford()
{

}

void backtrack(int node, int step)
{

}

void build(int a, int b, int c)
{
    if(toll[b])
    {

    }
    else
    {

    }
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> toll[i];
    }
    
    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        build(a, b, c);
    }

    bellman_ford();
    backtrack(1, lastStep);

    std::cout << ans << " " << indexes.size();
    std::reverse(indexes.begin(), indexes.end());
    for(auto &i : indexes)
    {
        std::cout << i.first << " " << i.second << "\n";
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
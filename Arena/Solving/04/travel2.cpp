#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 80 + 5;
const int MAXM = 500 + 5;
const int INF = 1e9 + 10;

int n, m;
bool toll[MAXN];

struct Edge
{
    int to;
    int w;
    int tolls;
};

std::vector<Edge> g[MAXN];

void build(int a, int b, int c)
{
    
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
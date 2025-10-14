#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 2 * 1e5 + 10;
const int SQRT = 450;

int n, m, q;
std::vector<int> g[MAXN];
bool type[MAXN];
int number[MAXN];

void solve()
{
    std::cin >> n >> m >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        number[i] = i;
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);

        if(g[a].size() >= SQRT) type[a] = 1;
        if(g[b].size() >= SQRT) type[b] = 1;
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int x; 
        std::cin >> x;

        for(int j = 0 ; j < g[x].size() ; ++j)
        {
            number[g[x][j]] = number[x];
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << number[i] << " ";
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
    
    return 0;
}
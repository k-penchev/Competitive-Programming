#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 2 * 1e5 + 10;
const int SQRT = 450;

int n, m, q;
std::vector<int> g[MAXN], big_g[MAXN];

struct Tag
{
    int v;
    int time;
};

Tag number[MAXN], lazy[MAXN];

void find_number(int node)
{
    for(int i : big_g[node])
    {
        if(number[node].time < lazy[i].time)
        {
            number[node] = lazy[i];
        }
    }
}

void solve()
{
    std::cin >> n >> m >> q;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        number[i] = {i, 0};
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j : g[i])
        {
            if(g[j].size() >= SQRT)
            {
                big_g[i].push_back(j);
            }
        }
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int x;
        std::cin >> x;

        find_number(x);

        if(g[x].size() >= SQRT)
        {
            lazy[x] = {number[x].v, i};
        }
        else
        {
            for(int j : g[x])
            {
                number[j] = {number[x].v, i};
            }
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        find_number(i);
        std::cout << number[i].v << " ";
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
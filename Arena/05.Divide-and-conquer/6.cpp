#include <iostream>
#include <algorithm>
#include <vector>

const int MAXQ = 2e5 + 10;

int n, m, q;
std::vector<std::vector<int>> table;

struct Query
{
    int x1, y1;
    int x2, y2;
    int idx;
};

std::vector<Query> query;
int ans[MAXQ];

void divide(int l, int r)
{
    if(l == r)
    {
        //compute
        return;
    }

    int m = (l + r) / 2;

    divide(l, m);
    divide(m + 1, r);

    
}

void solve()
{
    std::cin >> n >> m >> q;

    table.resize(n, std::vector<int>(m));

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= m ; ++j)
        {
            std::cin >> table[i][j];
        }
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        query.push_back({x1, y1, x2, y2, i});
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
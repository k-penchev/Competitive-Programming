#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 10000;
const int MAXQ = 50000;

int n, q;

struct Box
{
    int w, v;
};

struct Query
{
    int l, r, w;
    int idx;
};

Box box[MAXN];
Query query[MAXQ];
int ans[MAXN];

void divide(int l, int r)
{
    if(l == r)
    {
        return;
    }

    int m = (l + r) / 2;
    divide(l, m); divide(m + 1, r);

    for(int i = 1 ; i <= q ; ++i)
    {
        if(query[i].l <= m && query[i].r > m)
        {

        }
    }
}

void solve()
{
    std::cin >> n;
    
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> box[i].w >> box[i].v;
    }

    std::cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        std::cin >> query[i].l >> query[i].r >> query[i].w;
        query[i].idx = i;
    }

    divide(1, n);

    for(int i = 1 ; i <= q ; ++i)
    {
        std::cout << ans[i] << "\n";
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
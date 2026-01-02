#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 10000 + 5;
const int MAXQ = 50000 + 5;
const int MAXW = 2000 + 5;

int n, q;

struct Item
{
    int w;
    int p;
};

struct Query
{
    int idx;
    int l, r;
    int w;
};

Item item[MAXN];
std::vector<Query> query;

int dpLeft[MAXN][MAXW];
int dpRight[MAXN][MAXW];
int output[MAXQ];

void divide(int l, int r, std::vector<Query> &qs)
{
    if(l == r)
    {
        for(auto [idx, qL, qR, w] : qs)
        {
            int ans = 0;
            if(item[l].w <= w) ans = item[l].p;
            output[idx] = ans;
        }

        return;
    }

    int mid = (l + r) >> 1;
    std::vector<Query> left;
    std::vector<Query> right;

    for(int i = 0; i <= MAXW - 1; ++i)
    {
        dpLeft[mid + 1][i] = 0;
        dpRight[mid][i] = 0;
    }

    for(int i = mid; i >= l; --i)
    {
        for(int j = 0; j <= MAXW - 1; ++j)
        {
            dpLeft[i][j] = dpLeft[i + 1][j];
        }

        for(int j = MAXW - 1; j >= item[i].w; --j)
        {
            dpLeft[i][j] = std::max(dpLeft[i][j], dpLeft[i][j - item[i].w] + item[i].p);
        }
    }

    for(int i = mid + 1; i <= r; ++i)
    {
        for(int j = 0; j <= MAXW - 1; ++j)
        {
            dpRight[i][j] = dpRight[i - 1][j];
        }

        for(int j = MAXW - 1; j >= item[i].w; --j)
        {
            dpRight[i][j] = std::max(dpRight[i][j], dpRight[i][j - item[i].w] + item[i].p);
        }
    }

    for(auto [idx, qL, qR, w] : qs)
    {
        if(qR <= mid)
        {
            left.push_back({idx, qL, qR, w});
            continue;
        }

        if(qL >= mid + 1)
        {
            right.push_back({idx, qL, qR, w});
            continue;
        }

        int W = std::min(w, MAXW - 1);
        int best = 0;

        for(int j = 0; j <= W; ++j)
        {
            best = std::max(best, dpLeft[qL][j] + dpRight[qR][W - j]);
        }

        output[idx] = best;
    }

    divide(l, mid, left);
    divide(mid + 1, r, right);
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> item[i].w >> item[i].p;
    }

    std::cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        int l, r, w;
        std::cin >> l >> r >> w;
        query.push_back({i, l, r, w});
    }

    divide(1, n, query);

    for(int i = 1 ; i <= q ; ++i)
    {
        std::cout << output[i] << "\n";
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

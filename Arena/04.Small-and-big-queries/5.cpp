#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>

const int MAXN = 1e5 + 10;
const int MAXSQ = 320;

int n, m, k, q;
int bigSize, currIdx = 0;
std::vector<int> basket[MAXN];
std::vector<int> in[MAXN];

int ans[MAXSQ][MAXN];
int bigIdx[MAXN];
bool isBig[MAXN];
bool marked[MAXN];

void calculateAns(int heavyMushroom)
{
    bigIdx[heavyMushroom] = ++currIdx;

    for(int& b : in[heavyMushroom])
    {
        for(int& m : basket[b])
        {
            ans[bigIdx[heavyMushroom]][m] += b;
        }
    }
}

int query(int x, int y)
{
    //in[x], in[y]

    int ret = 0;

    for(int& b : in[x])
    {
        marked[b] = 1;
    }

    for(int& b : in[y])
    {
        if(marked[b])
        {
            ret += b;
        }
    }

    for(int& b : in[x])
    {
        marked[b] = 0;
    }

    return ret;
}

void solve()
{
    std::cin >> n >> m;
    bigSize = sqrt(n);

    for(int i = 1 ; i <= m ; ++i)
    {
        std::cin >> k;
        basket[i].resize(k);
        for(int j = 0 ; j < k ; ++j)
        {
            std::cin >> basket[i][j];
            in[basket[i][j]].push_back(i);
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(in[i].size() >= bigSize)
        {
            isBig[i] = 1;
            calculateAns(i);
        }
    }

    std::cin >> q;
    
    for(int i = 1 ; i <= q ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        
        if(in[a].size() < in[b].size()) std::swap(a, b);

        if(isBig[a])
        {
            std::cout << ans[bigIdx[a]][b] << "\n";
        }
        else
        {
            std::cout << query(a, b) << "\n";
        }
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
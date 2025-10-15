#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath> 

const int MAXN = 2e5 + 10;
const int BUCKET = 460;

int n, q;
int a[MAXN], cnt[MAXN];
bool included[MAXN];

bool isBig[MAXN];
std::vector<int> bigColor;
int ans[BUCKET][MAXN]; 

int query(int x, int y)
{
    int swaps = 0;
    std::fill(included + 1, included + n + 1, 0);

    int cnt1 = 0, cnt2 = 0;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(a[i] == x || a[i] == y)
        {
            included[i] = 1;
            cnt1 += 1;
        }
    }

    int pivot = (cnt1 / 2 + cnt1 % 2), pivot_idx = 0;
    for(int i = 1 ; i <= n ; ++i)
    {
        if(included[i])
        {
            cnt2 += 1;
        }
        
        if(cnt2 == pivot)
        {
            pivot_idx = i;
            break;
        }
    }

    
    int l = 0, r = 0;
    for(int j = pivot_idx - 1 ; j >= 1 ; --j)
    {
        if(included[j])
        {
            swaps += (pivot_idx - j - 1) - l;
            l += 1;
        }
    }

    for(int j = pivot_idx + 1 ; j <= n ; ++j)
    {
        if(included[j])
        {
            swaps += (j - pivot_idx - 1) - r;
            r += 1;
        }
    }

    return swaps;
}

void queryBig(int x, int y)
{
    ans[x][y] = query(x, y);
}

void solve()
{
    std::cin >> n >> q;
    int BUCKET_SIZE = static_cast<int>(std::sqrt(n));

    for(int i = 1 ; i <= n ; ++i)  
    {
        std::cin >> a[i];
        cnt[a[i]] += 1;
    }
    
    for(int i = 1 ; i <= n ; ++i)
    {
        if(cnt[i] >= BUCKET_SIZE)
        {
            isBig[i] = 1;
            bigColor.push_back(i);
        }
    }

    for(int i = 0 ; i < bigColor.size() ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            queryBig(bigColor[i], j);
        }
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int x, y;
        std::cin >> x >> y;

        if(isBig[x])
        {
            std::cout << ans[x][y] << "\n";
        }
        else if(isBig[y])
        {
            std::cout << ans[y][x] << "\n";
        }
        else
        {
            std::cout << query(x, y) << "\n";
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
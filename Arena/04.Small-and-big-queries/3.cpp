#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, c, l, r;
int a[MAXN], b[MAXN];
int ans[MAXN];
bool done[MAXN];

int calc(int t)
{
    for(int i = 1 ; i <= t ; ++i)
    {
        b[i] = a[i];
    }

    int ptr = 1, k = 1;
    for(int i = t + 1 ; i <= n ; ++i)
    {
        if(b[ptr] + c <= a[i])
        {
            b[ptr] = a[i];
            ptr += 1;

            if(ptr == t + 1)
            {
                ptr = 1;
                k += 1;
            }
        }
    }

    return k;
}

void solve()
{
    std::cin >> n >> c >> l >> r;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    std::sort(a + 1, a + n + 1);

    int curr = n;
    for(int t = 1 ; t <= n ; ++t)
    {
        int k0 = calc(t);

        for(int k = curr ; k > k0 ; --k)
        {
            ans[k] = t - 1;
        }

        curr = k0;
    }

    ans[1] = n;

    for(int k = l ; k <= r ; ++k)
    {
        std::cout << ans[k] << " ";
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
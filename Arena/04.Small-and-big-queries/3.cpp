#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, c, l, r;
int a[MAXN], b[MAXN];
int ans[MAXN];

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

    ans[1] = n;
    for(int k = 2 ; k <= n ; ++k) //t
    {
        int T = ans[k - 1];
        while(true)
        {
            int answer = calc(T);

            if(answer == k)
            {
                ans[k] = answer;
                break;
            }

            T -= 1;
        }
    }

    for(int i = l ; i <= r ; ++i)
    {
        std::cout << ans[i] << " ";
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
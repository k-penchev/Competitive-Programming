#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 500 + 5;

int n;
int a[MAXN][MAXN];
int b[MAXN][MAXN];
int c[MAXN][MAXN];
int r[MAXN];

int b_r[MAXN];
int c_r[MAXN];
int a_b_r[MAXN];

bool compute()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        r[i] = rand() % 2;
    }

    //b * r
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            b_r[i] += b[i][j] * r[j];
        }
    }

    //a * (b * r)
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            a_b_r[i] += a[i][j] * b_r[j];
        }
    }

    //c * r
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            c_r[i] += c[i][j] * r[j];
        }
    }

    //a * (b * r) == c * r
    for(int i = 1 ; i <= n ; ++i)
    {
        if(a_b_r[i] != c_r[i])
        {
            return false;
        }
    }

    return true;
}   

void reset()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        b_r[i] = 0;
        c_r[i] = 0;
        a_b_r[i] = 0;
    }
}

void solve()
{
    bool res = 1;
    for(int i = 1 ; i <= 20 ; ++i)
    {
        res &= compute();
        reset();
    }

    std::cout << (res == 1 ? "YES" : "NO") << "\n";
}

void input()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            std::cin >> a[i][j];
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            std::cin >> b[i][j];
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            std::cin >> c[i][j];
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
    input();
    solve();
    
    return 0;
}
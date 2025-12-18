#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 2 * 1e5 + 10;

int n;
int a[MAXN];
int b[MAXN];
int c[MAXN];
int d[MAXN];

void init(std::vector<int> kids, const std::vector<int> candies)
{
    n = kids.size();

    for(int i = 1 ; i <= n ; ++i)
    {
        a[i] = kids[i - 1];
        b[i] = candies[i - 1];
        c[i] = b[i] - a[i];
    }
}

int prev(int l, int r, int idx)
{
    if(idx == l)
    {
        return r;
    }

    return idx - 1;
}

int next(int l, int r, int idx)
{
    if(idx == r)
    {
        return l;
    }
    
    return idx + 1;
}

bool isValid(int l, int r)
{
    l += 1; r += 1;
    int m = r - l + 1;

    if(m == 1) return b[l] >= a[l];

    long long totalA = 0, totalB = 0;
    for(int i = l; i <= r; ++i)
    {
        totalA += a[i];
        totalB += b[i];
    }
    
    if(totalA > totalB) return 0; 

    for(int start = l; start <= r; ++start)
    {
        long long extra = b[prev(l, r, start)];
        long long sumA = 0, sumB = 0;

        int pos = start;
        for(int len = 1; len <= m - 1; ++len) 
        {
            sumA += a[pos];
            sumB += b[pos];

            if(sumA > sumB + extra) return 0;

            pos = next(l, r, pos);
        }
    }

    return 1;
}


void update(int l, int r, int x, int y)
{
    l += 1, r += 1;

    for(int i = l ; i <= r ; ++i)
    {
        a[i] = x;
        b[i] = y;
        c[i] = b[i] - a[i];
    }
}
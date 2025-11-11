#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <numeric>

int n, k;
std::vector<int> a;

int compare(int x, int y); //returns x if perm[x] > perm[]

void divide(int l, int r)
{
    if(l == r)
    {
        return;
    }

    int m = (l + r) / 2;
    divide(l, m); divide(m + 1, r);

    std::vector<int> left(m - l + 1, 0);
    std::vector<int> right(r - m, 0);

    for(int i = 0 ; i < m - l + 1 ; ++i)
    {
        left[i] = a[l + i];
    }

    for(int i = 0 ; i < r - m ; ++i)
    {
        right[i] = a[m + 1 + i];
    }

    int ptr1 = 0, ptr2 = 0;
    for(int i = 0 ; i < (r - l + 1) ; ++i)
    {
        if(ptr1 == m - l + 1)
        {
            a[l + i] = right[ptr2++];
            continue;
        }

        if(ptr2 == r - m)
        {
            a[l + i] = left[ptr1++];
            continue;
        }

        if(compare(left[ptr1], right[ptr2]) == right[ptr2])
        {
            a[l + i] = left[ptr1++];
        }
        else
        {
            a[l + i] = right[ptr2++];
        }
    }
}


std::vector<int> biggest(int N, int K)
{
    n = N;
    k = K;

    a.resize(n + 1);
    std::iota(a.begin() + 1, a.end(), 1);

    divide(1, n);

    std::vector<int> res;
    for(int i = n; i >= n - k + 1 ; --i)
    {
        res.push_back(a[i]);
    }

    return res;
}
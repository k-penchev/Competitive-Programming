#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <random>

int get_lis_length(const std::vector<int>& p);

std::vector<int> rotateToBack(std::vector<int> p, int pos)
{
    int temp = p[pos];

    for(int i = pos ; i < p.size() - 1 ; ++i)
    {
        p[i] = p[i + 1];
    }

    p[p.size() - 1] = temp;

    return p;
}

std::vector<int> rotateToFront(std::vector<int> p, int pos)
{
    int temp = p[pos];

    for(int i = pos ; i >= 1 ; --i)
    {
        p[i] = p[i - 1];
    }

    p[0] = temp;

    return p;
}

int find_maximum(int n)
{
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);

    int prev = get_lis_length(p);
    
    while(true)
    {
        std::vector<int> w = rotateToFront(p, n - 1);
        int curr = get_lis_length(w);

        if(prev > curr)
        {
            break;
        }

        p = w;
        prev = curr;
    }

    
    for(int i = 0 ; i < n ; ++i)
    {
        std::vector<int> w = rotateToBack(p, i);
        int curr = get_lis_length(w);

        if(prev < curr)
        {
            p = w;
            prev = curr;
            i -= 1;
        }
    }

    return p[n - 1];
}
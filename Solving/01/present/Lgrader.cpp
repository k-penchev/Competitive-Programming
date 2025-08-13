#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "present.h"
#include "present.cpp"

const int __maxn = 350000 + 10;

int __n, __q, __l;
int __a[__maxn];
int __for_nth_element[__maxn];
std::vector < int > __v;

int question(int x, int k)
{
    for (int i = 0 ; i < x ; ++i)
    {
        __for_nth_element[i] = __a[i];
    }

    std::nth_element(__for_nth_element, __for_nth_element+k-1, __for_nth_element+x);
    return __for_nth_element[k-1];
}

void fastIO()
{
    std::ios_base :: sync_with_stdio(0);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void read()
{
    std::cin >> __n;
    for (int i = 0 ; i < __n ; ++i)
    {
        std::cin >> __a[i];
    }
}

void checkResult()
{
    bool bl = 1;
    for (int i = 0 ; i < __n && bl ; ++i)
        bl &= (__a[i] == __v[i]);

    if (bl) std::cout << "OK\n";
    else std::cerr << "Wrong answer! Different elements!\n";
}

int main ()
{
    fastIO();
    read();

    __v = solve(__n);

    std::cerr << "result:\n";
    for (int i = 0 ; i < __n ; ++i)
        std::cout << __v[i] << ' ';
    std::cout << '\n';

    checkResult();
    return 0;
}

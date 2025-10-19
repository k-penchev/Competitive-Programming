#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 128;

int n;
int a[MAXN];
std::vector<int> swaps;

bool isSorted()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = i + 1 ; j <= n ; ++j)
        {
            if(a[i] > a[j]) return false;
        }
    }

    return true;
}

// a[l ... m] ; a[m + 1 ... r]
void conquer(int l, int m, int r)
{
    int ptr = 2;
    while(!isSorted())
    {
        int current = a[ptr];

        for(int i = ptr ; i >= l ; --i)
        {
            a[i] = a[i - 1];
        }

        a[l] = current;
        swaps.push_back(ptr);
        
        ptr <<= 1;
        if(ptr > r) ptr = 2;
    }
}

void divide(int l, int r)
{
    if(l >= r) return;

    int m = (l + r) / 2;

    divide(l, m);
    divide(m + 1, r);

    conquer(l, m, r);
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    divide(1, n);

    std::cout << swaps.size() << "\n";

    for(int s : swaps)
    {
        std::cout << s << " ";
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
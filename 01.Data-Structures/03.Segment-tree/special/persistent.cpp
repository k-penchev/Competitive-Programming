#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int MAXLOG = 17;

int n;
int a[MAXN];

struct PersistentSegmentTree
{
    struct Node
    {

    };

    void build()
    {

    }
};

PersistentSegmentTree tree;

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
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
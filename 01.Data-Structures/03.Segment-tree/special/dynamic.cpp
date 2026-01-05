#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 25000 + 10;
const int MAXLOG = 20;
const int INF = 1e9 + 10;

int n;
int a[MAXN];

struct DynamicSegmentTree
{
    struct Node
    {
        int sum;
        int left, right;

        Node()
        {
            sum = 0;
            left = right = 0;
        }
    };

    Node tree[2 * MAXN * MAXLOG];

    void update()
    {

    }

    int query()
    {
        
    }
};

DynamicSegmentTree tree;

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
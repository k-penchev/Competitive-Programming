#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#define int long long

const int MAXN = 200000 + 10;
const int INF = 1e18 + 10;

int n, m;
int a[MAXN], d[MAXN];

struct SegmentTree
{   
    struct Node
    {
        bool active;
        int ans;
        int head;
        int tail;
        int dp[2][2];

        Node()
        {
            active = false;
            ans = 0;
            head = tail = 0;
            dp[0][0] = dp[0][1] = dp[1][0] = dp[1][1] = -INF; 
        }

        Node(int val)
        {
            active = true;
            ans = std::max(0LL, std::abs(val));
            head = tail = val;
            dp[0][0] = 0;
            dp[1][1] = std::abs(val);
            dp[0][1] = dp[1][0] = -INF;
        }

        inline friend Node operator + (const Node &left, const Node &right)
        {
            if(!left.active) return right;
            if(!right.active) return left;

            Node result;
            result.active = true;
            
            for(int leftL : {0, 1})
            {
                for(int leftR : {0, 1})
                {
                    for(int rightL : {0, 1})
                    {
                        for(int rightR : {0, 1})
                        {
                            if(left.dp[leftL][leftR] == -INF || right.dp[rightL][rightR] == -INF)
                            {
                                continue;
                            }

                            if(leftR == 1 && rightL == 1)
                            {
                                int x = left.tail;
                                int y = right.head;
                                
                                if(x != 0 && y != 0 && x * y < 0)
                                {
                                    continue;
                                }
                            }
                        
                            int candidate = left.dp[leftL][leftR] + right.dp[rightL][rightR];
                            result.dp[leftL][rightR] = std::max(result.dp[leftL][rightR], candidate);
                            result.ans = std::max(result.ans, candidate);
                        }
                    }
                }
            }

            result.head = left.head;
            result.tail = right.tail;

            return result;
        }
    };

    Node tree[4 * MAXN];

    void build(int idx, int low, int high, int arr[])
    {
        if(low == high)
        {
            tree[idx] = Node(arr[low]);
            return;
        }

        int mid = (low + high) / 2;
        build(2 * idx, low, mid, arr);
        build(2 * idx + 1, mid + 1, high, arr);

        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            tree[idx] = Node(val);
            return;
        }

        int mid = (low + high) / 2;
        if(pos <= mid) update(2 * idx, low, mid, pos, val);
        else update(2 * idx + 1, mid + 1, high, pos, val);

        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }  

    void update(int pos, int val)
    {
        if(pos >= 1 && pos <= n)
        {
            d[pos] += val;  
            update(1, 1, n, pos, d[pos]);
        }
    }

    int query()
    {
        return tree[1].ans;
    }
};

SegmentTree tree;

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    n = n - 1;
    for(int i = 1 ; i <= n ; ++i)
    {
        d[i] = a[i] - a[i + 1];
    }

    tree.build(d);

    int l, r, x;
    for(int i = 1 ; i <= m ; ++i)
    {
        std::cin >> l >> r >> x;
        
        tree.update(l - 1, -x);
        tree.update(r, +x);

        std::cout << tree.query() << "\n";
    }
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
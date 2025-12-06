#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 1e5 + 10;

int n, q;
int a[MAXN];

struct SegmentTree
{
    struct Node
    {
        int sum;
        int lazy;

        Node()
        {
            sum = 0;
            lazy = 0;
        }

        Node(int val)
        {
            sum = val;
            lazy = 0;
        }

        inline friend Node operator + (const Node &left, const Node &right)
        {
            Node result;
            result.sum = left.sum + right.sum;
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

    void push(int idx, int low, int high)
    {
        if(!tree[idx].lazy)
        {
            return;
        }

        tree[idx].sum += tree[idx].lazy * (high - low + 1);
        if(low != high)
        {
            tree[2 * idx].lazy += tree[idx].lazy;
            tree[2 * idx + 1].lazy += tree[idx].lazy;
        }

        tree[idx].lazy = 0;
    }

    void update(int idx, int low, int high, int queryL, int queryR, int val)
    {
        if(queryL > queryR) return;

        push(idx, low, high);
        if(queryL > high || queryR < low)
        {
            return;
        }
        else if(queryL <= low && high <= queryR)
        {
            tree[idx].lazy += val;
            push(idx, low, high);
            return;
        }

        int mid = (low + high) / 2;
        update(2 * idx, low, mid, queryL, queryR, val);
        update(2 * idx + 1, mid + 1, high, queryL, queryR, val);

        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }

    int get(int idx, int low, int high, int pos)
    {
        push(idx, low, high);
        if(low == high)
        {
            return tree[idx].sum;
        }

        int mid = (low + high) / 2;
        if(pos <= mid) return get(2 * idx, low, mid, pos);
        else return get(2 * idx + 1, mid + 1, high, pos);
    }

    int binaryFirstEqual(int x)
    {
        int l = 0, r = n + 1;

        while(l + 1 < r)
        {
            int mid = (l + r) / 2;

            if(get(1, 1, n, mid) >= x) r = mid;
            else l = mid;
        }

        return r;
    }

    int binaryFirstBigger(int x)
    {
        int l = 0, r = n + 1;

        while(l + 1 < r)
        {
            int mid = (l + r) / 2;

            if(get(1, 1, n, mid) > x) r = mid;
            else l = mid;
        }

        return r;
    }
};

SegmentTree tree;

void solve()
{
    std::cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    std::sort(a + 1, a + n + 1);
    tree.build(1, 1, n, a);

    for(int i = 1 ; i <= q ; ++i)
    {
        char type;
        int x, y;
        std::cin >> type >> x >> y;

        if(type == 'F')
        {
            int l = tree.binaryFirstEqual(y);
            if(l == n + 1) continue; 
            int r = std::min(l + x - 1, n);

            if(r == n)
            {
                tree.update(1, 1, n, l, n, +1);
                continue;
            }

            int splitElement = tree.get(1, 1, n, r);

            int first = tree.binaryFirstEqual(splitElement);
            int second = tree.binaryFirstBigger(splitElement) - 1;

            int leftOver = x - (first - l);
            int l2 = second - leftOver + 1;

            tree.update(1, 1, n, l, first - 1, +1);
            tree.update(1, 1, n, l2, second, +1);
        }
        else
        {
            std::cout << tree.binaryFirstBigger(y) - tree.binaryFirstEqual(x) << "\n";
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
    solve();
}
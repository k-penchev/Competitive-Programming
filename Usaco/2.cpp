#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#define int long long

const int MAXN = 500000 + 10;

int n, m;
std::string s;
int a[MAXN];

struct SegmentTree
{
    struct Node
    {
        bool active;
        int ans;
        int inside;
        int prefix;
        int suffix;

        Node()
        {
            active = false;
            ans = inside = prefix = suffix = 0;
        }

        Node(int val)
        {
            active = true;
            ans = (val == +1);
            inside = val;
            prefix = suffix = (val == +1);
        }

        inline friend Node operator + (const Node &left, const Node &right)
        {
            if(!left.active)
            {
                return right;
            }

            if(!right.active)
            {
                return left;
            }

            Node result;
            result.active = true;
            result.inside = left.inside + right.inside;
            result.prefix = std::max(left.prefix, left.inside + right.prefix);
            result.suffix = std::max(right.suffix, right.inside + left.suffix);
            result.ans = std::max({left.ans + right.inside, left.inside + right.ans, left.prefix + right.suffix});
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

    Node query(int idx, int low, int high, int qL, int qR)
    {
        if(qL > high || qR < low)
        {
            return Node();
        }
        else if(qL <= low && high <= qR)
        {
            return tree[idx];
        }

        int mid = (low + high) / 2;

        Node res;
        res = res + query(2 * idx, low, mid, qL, qR);
        res = res + query(2 * idx + 1, mid + 1, high, qL, qR);
        return res;
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r).ans;
    }
};

SegmentTree tree;

void solve()
{
    std::cin >> n >> s;

    for(int i = 1 ; i <= n ; ++i)
    {
        a[i] = (s[i - 1] == 'T' ? 1 : -1);
    }

    tree.build(a);

    std::cin >> m;
    for(int i = 1 ; i <= m ; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << tree.query(l, r) << "\n";
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
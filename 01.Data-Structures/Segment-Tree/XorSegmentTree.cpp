#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = (1 << 20) + 10;
const int MAX_LOG = 30;

int n, q;
int a[MAXN];

struct Node
{
    int minVal;
    int maxVal;

    Node()
    {
        minVal = INT_MAX;
        maxVal = INT_MIN;
    }
};

struct SegmentTree
{
    Node seg[4 * MAXN];
    int lazy[MAX_LOG + 1];

    SegmentTree()
    {
        memset(seg, 0, sizeof(seg));
        memset(lazy, 0, sizeof(lazy));
    }

    Node combine(Node& left, Node& right)
    {
        Node res;

        res.minVal = min(left.minVal, right.minVal);
        res.maxVal = max(left.maxVal, right.maxVal);

        return res;
    }

    void build(int idx, int low, int high, int value, int pos)
    {
        if(low == high)
        {
            Node new_node;

            new_node.minVal = new_node.maxVal = pos;

            seg[idx] = new_node;

            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        if(value <= mid)
        {
            build(left, low, mid, value, pos);
        }
        else
        {
            build(right, mid + 1, high, value, pos);
        }
        
        seg[idx] = combine(seg[left], seg[right]);
    }

    Node query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            return Node();
        }
        else if(queryL <= low && high <= queryR)
        {
            return seg[idx];
        }


        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        int range = (high - low + 1);
        int depth = log2(range);

        if(lazy[depth])
        {
            swap(left, right);
        }

        Node le, ri;

        le = query(left, low, mid, queryL, queryR);
        ri = query(right, mid + 1, high, queryL, queryR);

        return combine(le, ri);
    }

    void build(int value, int pos)
    {
        build(1, 1, n, value, pos);
    }

    int query(int l, int r)
    {
        Node res = query(1, 1, n, l, r);

        return res.maxVal - res.minVal + 1;
    }

    void update(int x)
    {
        int depth = 1;

        while(x)
        {
            if(x % 2 == 1)
            {
                lazy[depth] ^= 1;
            }

            x /= 2;
            depth++;
        }
    }
};

SegmentTree tree;

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i]; ++a[i];
        tree.build(a[i], i);
    }

    string qType;
    int x, y;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> qType;

        if(qType == "Update")
        {
            cin >> x;
            tree.update(x);
        }
        else
        {
            cin >> x >> y; ++x, ++y;
            cout << tree.query(x, y) << "\n";
        }
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;

int n, q;
int a[MAXN];
bool d[MAXN];

struct Node
{
    int cntDiv;
    int evenSum, oddSum;
    int maxPrefix, maxSuffix;
    bool ending;

    Node()
    {
        cntDiv = 0;
        evenSum = oddSum = 0;
        maxPrefix = maxSuffix = 0;
        ending = false;
    }
};

struct SegmentTree
{
    Node seg[4 * MAXN];

    Node combine(Node left, Node right)
    {
        if(left.cntDiv == -1) return right;
        if(right.cntDiv == -1) return left;

        Node res;

        bool hasBorder = left.ending;

        res.cntDiv = left.cntDiv + right.cntDiv;
        res.ending = right.ending;


        if(hasBorder)
        {
            
            if(left.cntDiv % 2 == 1)
            {
                res.evenSum = left.evenSum + right.oddSum;
                res.oddSum = left.oddSum + right.evenSum;
            }
            else
            {
                res.evenSum = left.evenSum + right.evenSum;
                res.oddSum = left.oddSum + right.oddSum;
            }

            res.maxPrefix = left.maxPrefix;
            res.maxSuffix = right.maxSuffix;
        }
        else
        {
            if (left.cntDiv % 2 == 1)
            {
                res.oddSum = left.oddSum + right.evenSum - left.maxSuffix - right.maxPrefix + std::max(left.maxSuffix, right.maxPrefix);
                res.evenSum = left.evenSum + right.oddSum;
            }
            else
            {
                res.oddSum = left.oddSum + right.oddSum;
                res.evenSum = left.evenSum + right.evenSum - left.maxSuffix - right.maxPrefix + std::max(left.maxSuffix, right.maxPrefix);
            }

            res.maxPrefix = left.maxPrefix;

            if(left.cntDiv == 0)
            {
                res.maxPrefix = max(res.maxPrefix, right.maxPrefix);
            }

            res.maxSuffix = right.maxSuffix;

            if(right.cntDiv == 0)
            {
                res.maxSuffix = max(res.maxSuffix, left.maxSuffix);
            }
        }
    

        return res;
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            a[low] += val;

            Node new_node;

            new_node.cntDiv = d[low];

            if(new_node.cntDiv == 0)
            {
                new_node.maxSuffix = a[low];
            }
            else
            {
                new_node.maxSuffix = 0;
            }


            new_node.evenSum = new_node.maxPrefix = a[low];
            new_node.oddSum = 0;
            new_node.ending = d[low];


            seg[idx] = new_node;
            
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        if(pos <= mid)
        {
            update(left, low, mid, pos, val);
        }
        else
        {
            update(right, mid + 1, high, pos, val);
        }

        seg[idx] = combine(seg[left], seg[right]);
    }

    void update(int pos, int val)
    {
        update(1, 1, n, pos, val);
    }

    Node query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            Node res; res.cntDiv = -1;
            return res;
        }
        else if(queryL <= low && high <= queryR)
        {
            return seg[idx];
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        Node le, ri;
        
        le = query(left, low, mid, queryL, queryR);
        ri = query(right, mid + 1, high, queryL, queryR);
        
        return combine(le, ri);
    }

    pair<int, int> query(int l, int r)
    {
        Node result;
        result = query(1, 1, n, l, r);
        
        return {result.evenSum, result.oddSum};
    }
};

struct Fenwick
{
    int bit[MAXN];

    void update(int idx, int val)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] += val;
        }
    }

    int query(int idx)
    {
        int sum = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            sum += bit[idx];
        }

        return sum;
    }
};

SegmentTree seg;
Fenwick fen;

void solve()
{
    cin >> n >> q;

    int qType, x, y;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> qType;

        if(qType == 1)
        {
            cin >> x;
            d[x] = true;

            fen.update(x, +1);
            seg.update(x, 0);

        }
        else if(qType == 2)
        {
            cin >> x;
            d[x] = false;

            fen.update(x, -1);
            seg.update(x, 0);

        }
        else if(qType == 3)
        {
            cin >> x >> y;

            seg.update(x, y);
        }
        else
        {
            cin >> x >> y;

            int parity = fen.query(x - 1);

            if(parity % 2 == 1) 
            {
                cout << seg.query(x, y).first << "\n";   // evenSum
            }
            else
            {
                cout << seg.query(x, y).second << "\n";  // oddSum
            }
        }
    }
}

void fastIO()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();

    return 0;
}

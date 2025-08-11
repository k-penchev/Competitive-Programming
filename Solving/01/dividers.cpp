#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int LOG = 17;

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
        ending = 0;
    }
};

struct SegmentTree
{
    Node tree[4 * MAXN];

    Node combine(Node left, Node right, int mid_idx)
    {
        if (left.cntDiv == -1) return right;
        if (right.cntDiv == -1) return left;

        Node res;

        res.cntDiv = left.cntDiv + right.cntDiv;

        //pref, suff

        if(!d[mid_idx] && left.cntDiv == 0) res.maxPrefix = max(left.maxPrefix, right.maxPrefix);
        else res.maxPrefix = left.maxPrefix;

        if(!d[mid_idx] && right.cntDiv == 0) res.maxSuffix = max(left.maxSuffix, right.maxSuffix);
        else res.maxSuffix = right.maxSuffix;

        bool cut = d[mid_idx];

        if (cut)
        {
            if (left.cntDiv & 1)
            {
                res.oddSum  = left.oddSum  + right.evenSum;
                res.evenSum = left.evenSum + right.oddSum;
            }
            else
            {
                res.oddSum  = left.oddSum  + right.oddSum;
                res.evenSum = left.evenSum + right.evenSum;
            }
        }
        else
        {
            if (left.cntDiv & 1)
            {
                res.oddSum  = left.oddSum  + right.evenSum - left.maxSuffix - right.maxPrefix + max(left.maxSuffix, right.maxPrefix); // repair here
                res.evenSum = left.evenSum + right.oddSum;                 // no repair
            } else
            {
                res.oddSum  = left.oddSum  + right.oddSum;                 // no repair
                res.evenSum = left.evenSum + right.evenSum - left.maxSuffix - right.maxPrefix + max(left.maxSuffix, right.maxPrefix);  // repair here
            }
        }

        res.ending = right.ending;
        
        return res;
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            a[low] += val;
            tree[idx].cntDiv = d[low];

            tree[idx].evenSum = a[low];
            tree[idx].maxPrefix = a[low];

            tree[idx].oddSum = 0;
            tree[idx].maxSuffix = ( (d[low]) ? 0 : a[low]);
            
            tree[idx].ending = d[low];

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

        tree[idx] = combine(tree[left], tree[right], mid);
    }

    Node query(int idx, int low, int high, int L, int R) {
        if (R < low || high < L) { Node z; z.cntDiv = -1; return z; } // empty
        if (L <= low && high <= R) return tree[idx];
        int mid = (low+high)/2;
        Node le = query(idx*2, low, mid, L, R);
        Node ri = query(idx*2+1, mid+1, high, L, R);
        if (le.cntDiv == -1) return ri;
        if (ri.cntDiv == -1) return le;
        return combine(le, ri, mid);
    }

};

struct Fenwick
{
    
    int bit[MAXN];

    void set()
    {
        for(int i = 0 ; i <= n ; i++)
        {
            bit[i] = 0;
        }
    }

    void update(int idx, int val)
    {
        while(idx <= n)
        {
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int query(int idx)
    {
        int sum = 0;

        while(idx >= 1)
        {
            sum += bit[idx];
            idx -= idx & (-idx);
        }

        return sum;
    }
};


Fenwick fen;
SegmentTree seg;


void solve()
{
    cin >> n >> q;

    fen.set();

    int qType, x, y;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> qType;

        if(qType == 1)
        {
            cin >> x;
            d[x] = 1;
            fen.update(x, +1);
            seg.update(1, 1, n, x, 0);
            
        }
        else if(qType == 2)
        {
            cin >> x;
            d[x] = 0;
            fen.update(x, -1);
            seg.update(1, 1, n, x, 0);
        }
        else if(qType == 3)
        {
            cin >> x >> y;
            seg.update(1, 1, n, x, y);
        }
        else
        {
            cin >> x >> y;
            
            int parity = fen.query(x - 1);
            
            if(parity % 2 == 1)
            {
                cout << seg.query(1, 1, n, x, y).oddSum << "\n";
            }
            else
            {
                cout << seg.query(1, 1, n, x, y).evenSum << "\n";
            }
            
        }
    }
}

/*


10 20
1 4
3 3 7
3 4 1
3 5 8
3 6 5
4 3 6
1 1
4 3 6
3 10 3
3 9 2
3 8 9
1 8
4 1 10
4 4 9
3 9 8
1 7
3 2 6
4 2 9
2 1
4 2 9


*/


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
    
    return 0;
}
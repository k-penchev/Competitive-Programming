#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 100000 + 5;
const int NINF = (int)-4e18;
const int PINF = (int) 4e18;

int n;
int a[MAXN];
int dp[MAXN]; 
pair<int, int> toCompress[MAXN];
int compressed[MAXN];
int maxVal = 1;

struct Node
{
    int lisLen;
    int lisCnt;

    Node()
    {
        lisLen = lisCnt = 0;
    }

    Node(int len, int cnt)
    {
        lisLen = len;
        lisCnt = cnt;
    }
};

struct SegmentTree
{
    Node tree[4 * MAXN];

    SegmentTree()
    {
        for(int i = 1 ; i <= 4 * MAXN ; ++i)
        {
            tree[i] = Node();
        }
    }

    Node combine(const Node& left, const Node& right)
    {
        //left -> {4, 3} right -> {5, 2}

        if(left.lisLen == right.lisLen)
        {
            return Node(left.lisLen, left.lisCnt + right.lisCnt);
        }

        return (left.lisLen > right.lisLen ? left : right);
    }

    
    void update(int idx, int low, int high, int pos, Node& v)
    {
        if(low == high)
        {
            tree[idx] = combine(tree[idx], v);

            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        if(pos <= mid)
        {
            update(left, low, mid, pos, v);
        }
        else
        {
            update(right, mid + 1, high, pos, v);
        }

        tree[idx] = combine(tree[left], tree[right]);
    }

    Node query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            return Node();
        }
        else if(queryL <= low && high <= queryR)
        {
            return tree[idx];
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        Node le, ri;

        le = query(left, low, mid, queryL, queryR);
        ri = query(right, mid + 1, high, queryL, queryR);

        return combine(le, ri);
    }


    void update(int pos, pair<int, int>& val)
    {
        Node v(val.first, val.second);

        update(1, 1, maxVal, pos, v);
    }

    pair<int, int> query(int l, int r)
    {
        Node res = query(1, 1, maxVal, l, r);

        return {res.lisLen, res.lisCnt};
    }
};

SegmentTree tree;

int fast_lis_count()
{
    for(int i = 0 ; i < n ; ++i)
    {
        dp[i] = 1;
        toCompress[i] = {a[i], i};
    }

    sort(toCompress, toCompress + n);

    for(int i = 0 ; i < n ; ++i)
    {
        compressed[toCompress[i].second] = maxVal;
        if (i + 1 < n && toCompress[i].first != toCompress[i + 1].first) 
            maxVal++;
    }

    for(int i = 0 ; i < n ; ++i)
    {
        pair<int, int> best = tree.query(1, compressed[i] - 1); 

        pair<int, int> curr;

        curr.first = best.first + 1;
        curr.second = (best.first == 0 ? 1 : best.second);

        tree.update(compressed[i], curr);
    }

    return tree.query(1, maxVal).second;
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    cout << fast_lis_count() << "\n";
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
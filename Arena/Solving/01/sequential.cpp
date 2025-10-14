#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 1;
const int MAXQ = 2 * 1e5 + 1;

int n, q;
int perm[MAXN], answer[MAXQ];

struct Query
{
    int l, r;
    int idx;
};

Query queries[MAXQ];

struct Node
{
    int maxLen;
    int maxPrefix;
    int maxSuffix;
    int intervalLen;
    bool isUsed;

    Node()
    {
        maxLen = 0;
        maxPrefix = maxSuffix = 0;
        intervalLen = 1;
        isUsed = false;
    }
};

struct SegmentTree
{
    Node tree[4 * MAXN];

    void build(int idx, int low, int high)
    {
        tree[idx] = Node();
        tree[idx].intervalLen = high - low + 1;
        if (low == high) return;

        int mid = (low + high) / 2;
        build(idx * 2, low, mid);
        build(idx * 2 + 1, mid + 1, high);
    }

    Node combine(const Node& left, const Node& right)
    {
        // 1 1 1 0 0 , 0 0 1 0 1 0 1 1
        Node res;

        int cross =  left.maxSuffix + right.maxPrefix;
        
        res.maxLen = max({left.maxLen, right.maxLen, cross});
        res.intervalLen = left.intervalLen + right.intervalLen;
        res.maxPrefix = left.maxPrefix;
        res.maxSuffix = right.maxSuffix;

        
        if(left.maxLen == left.intervalLen)
        {
            res.maxPrefix = max(res.maxPrefix, left.intervalLen + right.maxPrefix);
        }

        if(right.maxLen == right.intervalLen)
        {
            res.maxSuffix = max(res.maxSuffix, left.maxSuffix + right.intervalLen);
        }

        return res;
    }

    void update(int idx, int low, int high, int pos, bool isAdded)
    {
        if(low == high)
        {
            tree[idx] = Node();

            if(isAdded)
            {
                tree[idx].maxLen = tree[idx].maxPrefix = tree[idx].maxSuffix = 1;
                tree[idx].isUsed = true;
            }
            else
            {
                tree[idx].maxLen = tree[idx].maxPrefix = tree[idx].maxSuffix = 0;
                tree[idx].isUsed = false;
            }

            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        if(pos <= mid)
        {
            update(left, low, mid, pos, isAdded);
        }
        else
        {
            update(right, mid + 1, high, pos, isAdded);
        }

        tree[idx] = combine(tree[left], tree[right]);
    }

    void build()
    {
        build(1, 1, n);
    }

    void update(int pos, bool isAdded)
    {
        update(1, 1, n, pos, isAdded);
    }

    int query()
    {
        return tree[1].maxLen;
    }
};

SegmentTree tree;

void solve()
{

    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> perm[i];
    }

    tree.build();

    int l, r;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> l >> r;
        queries[i] = {l, r, i};
    }

    const int SQRT = sqrt(n);

    sort(queries + 1, queries + q + 1, [&](const Query& q1, const Query& q2)
    {
        if(q1.l / SQRT == q2.l / SQRT)
        {
            return q1.r < q2.r;
        }

        return ((q1.l / SQRT) < (q2.l / SQRT));
    });


    int lPtr = 1, rPtr = 0;

    for(int i = 1 ; i <= q ; ++i)
    {
        auto [l, r, idx] = queries[i];

        while(lPtr > l)
        {
            //add
            --lPtr;
            tree.update(perm[lPtr], true);
        }

        while(rPtr < r)
        {
            //add
            ++rPtr;
            tree.update(perm[rPtr], true);
        }

        while(lPtr < l)
        {
            //remove
            tree.update(perm[lPtr], false);
            lPtr++;
        }

        while(rPtr > r)
        {
            //remove
            tree.update(perm[rPtr], false);
            rPtr--;
        }

        answer[idx] = tree.query();
    }


    for(int i = 1 ; i <= q ; ++i)
    {
        cout << answer[i] << "\n";
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
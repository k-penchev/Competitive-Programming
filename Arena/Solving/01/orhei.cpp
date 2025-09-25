#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 50 + 5;
const int MAXM = 1e5 + 10;

int n, m, t, q;
int a[MAXM], b[MAXM], c[MAXM];

struct Node
{
    int dist[MAXN];

    Node()
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            dist[i] = i;
        }
    }
};


struct SegmentTree
{
    Node tree[4 * MAXM];

    Node combine(Node& left, Node& right)
    {
        Node res;

        for(int startingIdx = 1 ; startingIdx <= n ; ++startingIdx)
        {
            int endingIdx = (right.dist[left.dist[startingIdx]]);
            res.dist[startingIdx] = endingIdx;
        }

        return res;
    }

    void build(int idx, int low, int high)
    {
        if(low == high)
        {
            tree[idx] = Node();

            int w = c[low];

            for(int startingIdx = 1 ; startingIdx <= n ; ++startingIdx)
            {
                int endingIdx = (startingIdx == a[w] ? b[w] : startingIdx);
                tree[idx].dist[startingIdx] = endingIdx;
            }

            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid);
        build(right, mid + 1, high);

        tree[idx] = combine(tree[left], tree[right]);
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            c[low] = val;
            int w = c[low];

            for(int startingIdx = 1 ; startingIdx <= n ; ++startingIdx)
            {
                int endingIdx = (startingIdx == a[w] ? b[w] : startingIdx);
                tree[idx].dist[startingIdx] = endingIdx;
            }

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

    void build()
    {
        build(1, 1, t);
    }

    void update(int pos, int val)
    {
        update(1, 1, t, pos, val);
    }

    int query(int l, int r, int s)
    {
        Node res = query(1, 1, t, l, r);
        return res.dist[s];
    }
};

SegmentTree tree;

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        cin >> a[i] >> b[i];
    }

    cin >> t;

    for(int i = 1 ; i <= t ; ++i)
    {
        cin >> c[i];
    }

    tree.build();

    cin >> q;

    int qType, x, y, z; 

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> qType;

        if(qType == 1)
        {
            cin >> x >> y >> z;
            cout << tree.query(x, y, z) << "\n";
        }
        else
        {
            cin >> x >> y;
            tree.update(x, y);
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
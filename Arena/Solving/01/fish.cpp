#include <bits/stdc++.h>

using namespace std;

typedef long long llong;

const int MAXN = 1e6 + 5;
const int MAXQ = 2 * 1e5 + 5;

int n, q;

llong a[MAXN], val[MAXN];
char type[MAXN];
llong lIdx[MAXN], rIdx[MAXN];
llong activeCnt[MAXN];
vector<llong> toCompress;
unordered_map<llong, llong> compressed;

struct Node
{
    llong maxLen;
    llong maxPrefix;
    llong maxSuffix;
    llong usedCnt;
    llong intervalLen;

    Node()
    {
        maxLen = 0;
        maxPrefix = maxSuffix = 0;
        usedCnt = 0;
        intervalLen = 0;
    }
};

struct SegmentTree
{
    Node tree[4 * MAXN];

    Node combine(Node left, Node right)
    {
        Node res;

        llong cross = left.maxSuffix + right.maxPrefix;

        res.maxLen = max({left.maxLen, right.maxLen, cross});
        res.maxPrefix = left.maxPrefix;
        res.maxSuffix = right.maxSuffix;
        res.intervalLen = left.intervalLen + right.intervalLen;

        
        if(left.maxPrefix == left.intervalLen)
        {
            res.maxPrefix = max(res.maxPrefix, left.intervalLen + right.maxPrefix);
            
        }
        
        if(right.maxSuffix == right.intervalLen)
        {
            res.maxSuffix= max(res.maxSuffix, left.maxSuffix + right.intervalLen);
        }

        return res;
    }

    void build(int idx, int low, int high)
    {
        if(low == high)
        {
            Node new_node;

            new_node.intervalLen = 1;

            if(activeCnt[low])
            {
                new_node.maxLen = 1;
                new_node.maxPrefix = 1;
                new_node.maxSuffix = 1;
                new_node.usedCnt = activeCnt[low];
            }

            tree[idx] = new_node;

            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid);
        build(right, mid + 1, high);

        tree[idx] = combine(tree[left], tree[right]);
    }

    void update(int idx, int low, int high, int pos, llong delta)
    {
        if(low == high)
        {
            tree[idx].usedCnt += delta;
            tree[idx].intervalLen = 1;

            if(tree[idx].usedCnt == 1)
            {
                tree[idx].maxLen = tree[idx].maxPrefix = tree[idx].maxSuffix = 1;
            }
            else if(tree[idx].usedCnt == 0)
            {
                tree[idx].usedCnt = 0; 
                tree[idx].maxLen = tree[idx].maxPrefix = tree[idx].maxSuffix = 0;
            }

            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;


        if(pos <= mid)
        {
            update(left, low, mid, pos, delta);
        }
        else
        {
            update(right, mid + 1, high, pos, delta);
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
        build(1, 1, MAXN);
    }

    void update(int pos, int delta)
    {
        update(1, 1, MAXN, pos, delta);
    }

    llong query(int l, int r)
    {
        Node res = query(1, 1, MAXN, l, r);
        return res.maxLen;
    }
};

SegmentTree tree;


void compress()
{
    sort(toCompress.begin(), toCompress.end());

    int cnt = 1;

    for(int i = 0 ; i < toCompress.size(); ++i)
    {
        compressed[toCompress[i]] = cnt;

        if(i + 1 == toCompress.size()) break;

        if(toCompress[i] == toCompress[i + 1] - 1)
        {
           cnt++; 
        }
        else if(toCompress[i] != toCompress[i + 1])
        {
            cnt += 2;
        }
    }
}

void solve()
{
    compress();

    for(int i = 1 ; i <= n ; ++i)
    {
        activeCnt[compressed[a[i]]]++;
    }

    tree.build();

    for(int i = 1 ; i <= q ; ++i)
    {
        if(type[i] == '+')
        {
            tree.update(compressed[val[i]], +1);
        }
        else if(type[i] == '-')
        {
            tree.update(compressed[val[i]], -1);
        }
        else
        {
            cout << tree.query(compressed[lIdx[i]], compressed[rIdx[i]]) << "\n";
        }
    }

}

void input()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        toCompress.push_back(a[i]);
    }
    
    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> type[i];

        if(type[i] == '+')
        {
            cin >> val[i];
            toCompress.push_back(val[i]);
        }
        else if(type[i] == '-')
        {
            cin >> val[i];
            toCompress.push_back(val[i]);
        }
        else
        {
            cin >> lIdx[i] >> rIdx[i];
            toCompress.push_back(lIdx[i]);
            toCompress.push_back(rIdx[i]);
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
    input();
    solve();

    return 0;
}
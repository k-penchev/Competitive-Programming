#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAX_LOG = 31;

int n, q;
int a[MAXN], b[MAXN];

struct Node
{

    int numCnt[MAX_LOG];
    int andVal[MAX_LOG];
    int orVal[MAX_LOG];

    Node()
    {
        for(int i = 0; i < MAX_LOG; ++i)
        {
            numCnt[i] = 0;
            orVal[i]  = 0;
            andVal[i] = (1 << MAX_LOG) - 1;
        }
    }
};


struct SegmentTree
{
    
    Node tree[4 * MAXN];

    Node combine(const Node& left, const Node& right)
    {
        Node res;

        for(int i = 0 ; i < MAX_LOG ; ++i)
        {
            res.numCnt[i] = left.numCnt[i] + right.numCnt[i];
            res.andVal[i] = left.andVal[i] & right.andVal[i];
            res.orVal[i] = left.orVal[i] | right.orVal[i];
        }

        return res;
    }

    void build(int idx, int low, int high)
    {
        if(low == high)
        {
            tree[idx] = Node(); 

            tree[idx].numCnt[b[low]] = 1;
            tree[idx].andVal[b[low]] = a[low];
            tree[idx].orVal[b[low]] = a[low];
        
            return;
        }   

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid);
        build(right, mid + 1, high);

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

};

SegmentTree tree;

int compute(int l, int r)
{
    Node result = tree.query(1, 1, n, l, r);

    long long pref[MAX_LOG] = {0};
    long long suff[MAX_LOG] = {0};

    pref[0] = result.orVal[0];
    
    for(int i = 1 ; i < MAX_LOG ; ++i)
    {
        pref[i] = pref[i - 1] | result.orVal[i];
    }

    suff[MAX_LOG - 1] = result.andVal[MAX_LOG - 1];

    for(int i = MAX_LOG - 2 ; i >= 0 ; --i)
    {
        suff[i] = suff[i + 1] & result.andVal[i];
    }


    bool flag = false;
    int leftCnt = 0, total = r - l + 1;

    for(int i = 0 ; i <= MAX_LOG - 1 ; ++i)
    {
        leftCnt += result.numCnt[i];

        if(leftCnt == 0) continue;
        if(total - leftCnt == 0) continue;

        if(pref[i] == suff[i + 1])
        {
            flag = true;
            break;
        }
    }


    if(flag)
    {
        return 1;
    }

    for(int i = 0 ; i < MAX_LOG ; ++i)
    {
        if(result.numCnt[i] < 2) continue;
        if(result.orVal[i] != result.andVal[i]) continue;

        if(pref[i] == suff[i])
        {
            flag = true;
            break;
        }
    }

    return flag;
}

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        b[i] = __builtin_popcount(a[i]);
    }

    tree.build(1, 1, n);

    int l, r;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> l >> r;
        string answer = (compute(l, r) == 1 ? "Yes" : "No");
        cout << answer << "\n"; 
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
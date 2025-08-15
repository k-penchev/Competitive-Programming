#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 5 * 1e5 + 10;

int n, q;
int a[MAXN];

struct Node
{
    vector<int> v;
    int maxInv;
    int maxNum;

    Node()
    {
        v = {};
        maxInv = 0;
        maxNum = INT_MIN;
    }
};

struct MST
{
    Node seg[4 * MAXN];

    int binary(Node& node, int number)
    {
        /*
        cout << "\n";
        cout << "Entering : " << number << "\n";

        for(int x : node.v)
        {
            cout << x << " ";
        }

        cout << "\n";
        */

        int lPtr = -1, rPtr = node.v.size();

        while(rPtr > lPtr + 1)
        {
            int mid = (lPtr + rPtr) / 2;

            if(node.v[mid] < number)
            {
                lPtr = mid;
            }
            else
            {
                rPtr = mid;
            }
        }

        //cout << lPtr << " " << rPtr << "\n";
        //cout << "\n";
        return lPtr;
    }

    Node combine(Node& left, Node& right)
    {
        if (left.v.empty())  return right;
        if (right.v.empty()) return left;

        Node res;

        res.maxNum = max(left.maxNum, right.maxNum);

        int idx = binary(right, left.maxNum);
        int cross = INT_MIN;     
        
        if(idx >= 0)
            cross = left.maxNum + right.v[idx];
        
        res.maxInv = max({left.maxInv, right.maxInv, cross});

        int lPtr = 0, rPtr = 0;
        res.v.reserve(left.v.size() + right.v.size());

        for(int i = 1 ; i <= left.v.size() + right.v.size(); ++i)
        {
            if(lPtr == left.v.size())
            {
                res.v.push_back(right.v[rPtr++]);
                continue;
            }

            if(rPtr == right.v.size())
            {
                res.v.push_back(left.v[lPtr++]);
                continue;
            }

            if(left.v[lPtr] < right.v[rPtr])
            {
                res.v.push_back(left.v[lPtr++]);
            }
            else
            {
                res.v.push_back(right.v[rPtr++]);
            }
        }

        return res;
    }

    void build(int idx, int low, int high)
    {
        if(low == high)
        {
            Node new_node;

            new_node.v.push_back(a[low]);
            new_node.maxInv = 0;
            new_node.maxNum = a[low];

            seg[idx] = new_node;

            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid);
        build(right, mid + 1, high);

        seg[idx] = combine(seg[left], seg[right]);
    }

    vector<int> searchNodes;
    
    void query(int idx, int low, int high, int queryL, int queryR, int k)
    {
        if(queryL > high || queryR < low)
        {
            return;
        }
        else if(queryL <= low && high <= queryR)
        {
            searchNodes.push_back(idx);
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;


        query(left, low, mid, queryL, queryR, k);
        query(right, mid + 1, high, queryL, queryR, k);

        return;
    }

    void build()
    {
        build(1, 1, n);
    }

    int query(int l, int r, int k)
    {
        searchNodes.clear();

        query(1, 1, n, l, r, k);

        Node res;

        for(int i : searchNodes)
        {
            res = combine(res, seg[i]);
        }

        return (res.maxInv <= k);
    }
};

MST tree;

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
    }

    tree.build();

    int l, r, k;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> l >> r >> k;
        cout <<  tree.query(l, r, k);
    }

    cout << "\n";
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
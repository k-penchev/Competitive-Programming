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

struct Fenwick
{
    Node bit[MAXN];

    Fenwick()
    {
        for(int i = 1 ; i <= MAXN ; ++i)
        {
            bit[i] = Node();
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

    void update(int idx, pair<int, int>& val)
    {
        Node v;

        v.lisLen = val.first;
        v.lisCnt = val.second;

        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] = combine(bit[idx], v);
        }
    }
    
    pair<int, int> query(int idx)
    {
        Node res;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            res = combine(res, bit[idx]);
        }

        return {res.lisLen, res.lisCnt};
    }

};

Fenwick tree;

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
        maxVal += (toCompress[i].first != toCompress[i + 1].first);
    }

    for(int i = 0 ; i < n ; ++i)
    {
        pair<int, int> best = tree.query(compressed[i] - 1); 

        pair<int, int> curr;

        curr.first = best.first + 1;
        curr.second = (best.first == 0 ? 1 : best.second);

        tree.update(compressed[i], curr);
    }

    return tree.query(maxVal).second;
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
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n;
int a[MAXN];
int byIndex[MAXN]; 

struct Fenwick
{
    int bitSize;
    std::vector<int> bit;

    void resize(int size)
    {
        bitSize = size;
        bit.resize(size + 1, 0);
    }

    void update(int idx, int val)
    {
        for(; idx <= bitSize ; idx += (idx & (-idx)))
        {
            bit[idx] += val;
        }
    }

    int query(int idx)
    {
        int s = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            s += bit[idx];
        }

        return s;
    }

    int querySmaller(int idx)
    {
        return query(idx - 1);
    }

    int queryBigger(int idx)
    {
        return query(bitSize) - query(idx);
    }
};

struct MST
{
    struct Node
    {
        std::vector<int> v;
        Fenwick fenwick;
    };

    Node tree[4 * MAXN];

    Node combine(const Node& left, const Node& right)
    {
        Node result;

        int size = left.v.size() - 1 + right.v.size() - 1;
        result.v.resize(size + 1);
        result.fenwick.resize(size);

        int l = 1, r = 1;
        for(int i = 1 ; i <= size ; ++i)
        {
            if(l == left.v.size())
            {
                result.v[i] = right.v[r++];
                continue;
            }

            if(r == right.v.size())
            {
                result.v[i] = left.v[l++];
                continue;
            }

            if(left.v[l] <= right.v[r])
            {
                result.v[i] = left.v[l++];
            }
            else
            {
                result.v[i] = right.v[r++];
            }
        }

        for(int i = 1 ; i <= size ; ++i)
        {
            result.fenwick.update(i, +1);
        }

        return result;
    }

    void build(int idx, int low, int high, int arr[])
    {
        if(low == high)
        {   
            tree[idx].v.resize(2);
            tree[idx].fenwick.resize(1);

            tree[idx].v[1] = arr[low];
            tree[idx].fenwick.update(1, +1);
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid, arr);
        build(right, mid + 1, high, arr);

        tree[idx] = combine(tree[left], tree[right]);
    }

    int binary(std::vector<int>& vec, int k)
    {
        return std::lower_bound(vec.begin(), vec.end(), k) - vec.begin();
    }

    //delete number
    void update(int idx, int low, int high, int delNum)
    {
        tree[idx].fenwick.update(binary(tree[idx].v, delNum), -1);

        if(low == high)
        {
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        if(byIndex[delNum] <= mid)
        {
            update(left, low, mid, delNum);
        }
        else
        {
            update(right, mid + 1, high, delNum);
        }
    }

    int calculateAns(Node& node, int qryNum, bool qryType)
    {
        if(qryType == 0) 
        {
            return node.fenwick.querySmaller(binary(node.v, qryNum));
        }
        else
        {   
            return node.fenwick.queryBigger(binary(node.v, qryNum));
        }
    }

    //query for number
    //0 -> smaller, 1 -> bigger
    int query(int idx, int low, int high, int queryL, int queryR, int qryNum, bool qryType)
    {
        if(queryL > high || queryR < low)
        {
            return 0;
        }
        else if(queryL <= low && high <= queryR)
        {
            return calculateAns(tree[idx], qryNum, qryType);
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        return query(left, low, mid, queryL, queryR, qryNum, qryType) +
               query(right, mid + 1, high, queryL, queryR, qryNum, qryType);
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }

    void update(int delNum)
    {
        update(1, 1, n, delNum);
    }

    int query(int l, int r, int qryNum, bool qryType)
    {
        return query(1, 1, n, l, r, qryNum, qryType);
    }
};

MST mst;
Fenwick invFenwick;
int answer = 0;

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        byIndex[a[i]] = i;
    }

    invFenwick.resize(n);
    for(int i = n ; i >= 1 ; --i)
    {
        answer += invFenwick.query(a[i] - 1);
        invFenwick.update(a[i], +1);
    }

    mst.build(a);

    std::cout << answer << " ";
    for(int i = 1 ; i <= n - 2 ; ++i)
    {
        int x;
        std::cin >> x;

        int p1 = mst.query(1, byIndex[x] - 1, x, 1);
        int p2 = mst.query(byIndex[x] + 1, n, x, 0);

        answer -= p1 + p2;

        mst.update(x);
        std::cout << answer << " ";
        
    }

    std::cout << "\n";
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
    
    return 0;
}
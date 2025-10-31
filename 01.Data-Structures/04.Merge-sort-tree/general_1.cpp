//Find the smallest number greater or equal to a specified number. No modification queries.
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

const int MAXN = 1e5 + 10;
const int INF = 1e9 + 10;

int n;
int a[MAXN];

struct MST
{
    struct Node
    {
        std::vector<int> v;

        Node() {}

        Node(int x)
        {
            v.push_back(x);
        }
    };

    Node tree[4 * MAXN];

    Node combine(const Node& left, const Node& right)
    {
        Node res;

        res.v.reserve(left.v.size() + right.v.size());

        int l = 0, r = 0;
        for(int i = 0 ; i < left.v.size() + right.v.size() ; ++i)
        {
            if(l == left.v.size())
            {
                res.v.push_back(right.v[r++]);
                continue;
            }

            if(r == right.v.size())
            {
                res.v.push_back(left.v[l++]);
                continue;
            }

            if(left.v[l] <= right.v[r])
            {
                res.v.push_back(left.v[l++]);
            }
            else
            {
                res.v.push_back(right.v[r++]);
            }
        }

        return res;
    };

    void build(int idx, int low, int high, int * arr)
    {
        if(low == high)
        {
            tree[idx] = Node(arr[low]);
            return;
        }

        int mid = (low + high) / 2;

        build(2 * idx, low, mid, arr);
        build(2 * idx + 1, mid + 1, high, arr);

        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    int binary(std::vector<int>& v, int k)
    {
        int l = -1, r = v.size();

        while(l + 1 < r)
        {
            int m = (l + r) / 2;

            if(v[m] < k) l = m;
            else r = m;
        }

        if(r == v.size()) return INF;
        
        return v[r];
    }

    int query(int idx, int low, int high, int queryL, int queryR, int k)
    {
        if(queryL > high || queryR < low)
        {
            return INF;
        }
        else if(queryL <= low && high <= queryR)
        {
            return binary(tree[idx].v, k);
        }

        int mid = (low + high) / 2;

        return std::min(query(2 * idx, low, mid, queryL, queryR, k),
                query(2 * idx + 1, mid + 1, high, queryL, queryR, k));
    }

    void build(int * arr)
    {
        build(1, 1, n, arr);
    }

    int query(int l, int r, int k)
    {
        return query(1, 1, n, l, r, k);
    }
};

MST tree;

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    tree.build(a);

    std::cout << tree.query(2, 4, 3) << " " << tree.query(1, 5, 2) << " " << tree.query(4, 5, 1) << "\n";
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
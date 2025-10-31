//Find the smallest number greater or equal to a specified number. No modification queries.
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

const int MAXN = 1e5 + 10;
const int INF = 1e9 + 10;

int n;
int a[MAXN];

struct MST
{
    struct Node
    {
        std::multiset<int> v;

        Node() {}

        Node(int x)
        {
            v.insert(x);
        }
    };

    Node tree[4 * MAXN];

    Node combine(const Node& left, const Node& right)
    {
        Node res;

        for(auto it = left.v.begin() ; it != left.v.end() ; ++it)
        {
            res.v.insert(*it);
        }

        for(auto it = right.v.begin() ; it != right.v.end() ; ++it)
        {
            res.v.insert(*it);
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

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            tree[idx].v.erase(tree[idx].v.find(a[pos]));
            tree[idx].v.insert(val);

            a[pos] = val;
            return;
        }

        int mid = (low + high) / 2;

        if(pos <= mid)
        {
            update(2 * idx, low, mid, pos, val);
        }
        else
        {
            update(2 * idx + 1, mid + 1, high, pos, val);
        }

        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    int query(int idx, int low, int high, int queryL, int queryR, int k)
    {
        if(queryL > high || queryR < low)
        {
            return INF;
        }
        else if(queryL <= low && high <= queryR)
        {
            auto it = std::lower_bound(tree[idx].v.begin(), tree[idx].v.end(), k);
            if(it == tree[idx].v.end()) return INF;
            
            return *it;
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
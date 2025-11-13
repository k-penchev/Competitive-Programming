#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 5 * 1e5 + 10;
const int INF = 1e18;

int n, q;
int a[MAXN];

struct MST
{
    struct Node
    {
        std::vector<int> v;
        int maxInversion;
        int maxElement;
    };

    Node tree[4 * MAXN];

    int binary(const std::vector<int> &v, int k)
    {
        int l = -1, r = v.size();

        while(l + 1 < r)
        {
            int m = (l + r) / 2;

            if(v[m] < k) l = m;
            else r = m;
        }

        return l;
    }

    Node mergeBuild(const Node &left, const Node &right)
    {
        Node result;

        int index = binary(right.v, left.maxElement);

        int cross;
        if(index != -1)
        {
            cross = left.maxElement + right.v[index];
        }
        else
        {
            cross = 0;
        }

        result.maxInversion = std::max({left.maxInversion, right.maxInversion, cross});

        int l = 0, r = 0;
        for(int i = 0 ; i < left.v.size() + right.v.size() ; ++i)
        {
            if(l == left.v.size())
            {
                result.v.push_back(right.v[r++]);
                continue;
            }

            if(r == right.v.size())
            {
                result.v.push_back(left.v[l++]);
                continue;
            }

            if(left.v[l] <= right.v[r])
            {
                result.v.push_back(left.v[l++]);
            }
            else
            {
                result.v.push_back(right.v[r++]);
            }
        }

        result.maxElement = std::max(left.maxElement, right.maxElement);
        return result;
    }

    void build(int idx, int low, int high, int * arr)
    {
        if(low == high)
        {
            tree[idx].v.push_back(arr[low]);
            tree[idx].maxElement = arr[low];
            tree[idx].maxInversion = 0;

            return;
        }

        int mid = (low + high) / 2;

        build(2 * idx, low, mid, arr);
        build(2 * idx + 1, mid + 1, high, arr);

        tree[idx] = mergeBuild(tree[2 * idx], tree[2 * idx + 1]);
    }

    std::vector<int> nodes;
    void query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            return;
        }
        else if(queryL <= low && high <= queryR)
        {
            nodes.push_back(idx);
            return;
        }

        int mid = (low + high) / 2;

        query(2 * idx, low, mid, queryL, queryR);
        query(2 * idx + 1, mid + 1, high, queryL, queryR);
    }

    void build(int * arr)
    {
        build(1, 1, n, arr);
    }

    int query(int l, int r, int k)
    {
        nodes.clear();
        query(1, 1, n, l, r);

        int currentElement = tree[nodes[0]].maxElement;
        int currentInversion = tree[nodes[0]].maxInversion;

        for(int i = 1 ; i < nodes.size() ; ++i)
        {
            int index = binary(tree[nodes[i]].v, currentElement);

            int cross;
            if(index != -1)
            {
                cross = currentElement + tree[nodes[i]].v[index];
            }
            else
            {
                cross = 0;
            }
            currentInversion = std::max({currentInversion, tree[nodes[i]].maxInversion, cross});
            currentElement = std::max(currentElement, tree[nodes[i]].maxElement);
        }

        return currentInversion <= k;
    }
};

MST tree;

void solve()
{
    std::cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    tree.build(a);
    for(int i = 1 ; i <= q ; ++i)
    {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << tree.query(l, r, k);
    }

    std::cout << "\n";
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
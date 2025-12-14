#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n, q;
int color[MAXN];
std::vector<int> tree[MAXN];

struct SegmentTree
{
    struct Node
    {
        int ansMe;
        int colorL;
        int colorR;
        int colorLazy;
        bool active;

        Node()
        {
            ansMe = 0;
            colorL = colorR = 0;
            colorLazy = 0;
            active = false;
        }

        Node(int c)
        {
            ansMe = 0;
            colorL = colorR = c;
            colorLazy = 0;
            active = true;
        }

        void rotate()
        {
            std::swap(colorL, colorR);
        }

        inline friend Node operator + (const Node &left, const Node &right)
        {
            if(!left.active)
            {
                return right;
            }

            if(!right.active)
            {
                return left;
            }

            Node result;
            result.ansMe = left.ansMe + right.ansMe + (left.colorR != right.colorL);
            result.colorL = left.colorL;
            result.colorR = right.colorR;
            result.colorLazy = 0;
            result.active = true;
            return result;
        }
    };

    Node seg[4 * MAXN];

    void build(int idx, int low, int high, int arr[])
    {
        if(low == high) 
        {
            seg[idx] = Node(arr[low]);
            return;
        }

        int mid = (low + high) / 2;
        build(2 * idx, low, mid, arr);
        build(2 * idx + 1, mid + 1, high, arr);

        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }

    void push(int idx, int low, int high)
    {
        if(!seg[idx].colorLazy)
        {
            return;
        }

        seg[idx].ansMe = 0;
        seg[idx].colorL = seg[idx].colorR = seg[idx].colorLazy;
    
        if(low != high)
        {
            seg[2 * idx].colorLazy = seg[idx].colorLazy;
            seg[2 * idx + 1].colorLazy = seg[idx].colorLazy;
        }

        seg[idx].colorLazy = 0;
    }

    void update(int idx, int low, int high, int queryL, int queryR, int c)
    {
        push(idx, low, high);

        if(queryL > high || queryR < low)
        {
            return;
        }
        else if(queryL <= low && high <= queryR)
        {
            seg[idx].colorLazy = c;
            push(idx, low, high);
            return;
        }

        int mid = (low + high) / 2;
        update(2 * idx, low, mid, queryL, queryR, c);
        update(2 * idx + 1, mid + 1, high, queryL, queryR, c);

        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }

    Node query(int idx, int low, int high, int queryL, int queryR)
    {
        push(idx, low, high);

        if(queryL > high || queryR < low)
        {
            return Node();
        }
        else if(queryL <= low && high <= queryR)
        {
            return seg[idx];
        }

        int mid = (low + high) / 2;

        Node res;
        res = res + query(2 * idx, low, mid, queryL, queryR);
        res = res + query(2 * idx + 1, mid + 1, high, queryL, queryR);
        return res;
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }

    void update(int l, int r, int c)
    {
        update(1, 1, n, l, r, c);
    }

    Node query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
};

namespace HLD
{
    SegmentTree seg;
    int parent[MAXN], depth[MAXN], size[MAXN];
    int top[MAXN], id[MAXN], flat[MAXN], counter = 1;

    void dfs(int node, int par, int currDepth)
    {
        parent[node] = par;
        depth[node] = currDepth;
        size[node] = 1;

        for(const int &to : tree[node])
        {
            if(to == par) continue;

            dfs(to, node, currDepth + 1);
            size[node] += size[to]; 
        }
    }

    void decompose(int node, int par, int head)
    {
        top[node] = head;
        id[node] = counter++;

        int heavyChild = -1, heavyChildSize = -1;
        for(const int &to : tree[node])
        {
            if(to == par) continue;

            if(size[to] > heavyChildSize)
            {
                heavyChild = to;
                heavyChildSize = size[to];
            }
        }

        if(heavyChild == -1) return;
        decompose(heavyChild, node, head);

        for(const int &to : tree[node])
        {
            if(to == par || to == heavyChild) continue;
            decompose(to, node, to);
        }
    }

    void build()
    {
        dfs(1, 0, 0);
        decompose(1, 0, 1);

        for(int i = 1 ; i <= n ; ++i)
        {
            flat[id[i]] = color[i];
        }

        seg.build(flat);
    }

    void updatePath(int a, int b, int c)
    {
        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]])
            {
                std::swap(a, b);
            }

            seg.update(id[top[a]], id[a], c);
            a = parent[top[a]];
        }

        if(depth[a] > depth[b])
        {
            std::swap(a, b);
        }

        seg.update(id[a], id[b], c);
    }

    void updateSubtree(int a, int c)
    {
        seg.update(id[a], id[a] + size[a] - 1, c);
    }

    int query(int a, int b)
    {
        SegmentTree::Node leftPath, rightPath;

        while(top[a] != top[b])
        {
            if(depth[top[a]] >= depth[top[b]])
            {
                SegmentTree::Node temp = seg.query(id[top[a]], id[a]);
                temp.rotate();
                leftPath = leftPath + temp;
                a = parent[top[a]];
            }
            else
            {
                rightPath = seg.query(id[top[b]], id[b]) + rightPath;
                b = parent[top[b]];
            }
        }

        if(depth[a] >= depth[b])
        {
            SegmentTree::Node temp = seg.query(id[b], id[a]);
            temp.rotate();
            leftPath = leftPath + temp;
        }
        else
        {
            rightPath = seg.query(id[a], id[b]) + rightPath;
        }

        return (leftPath + rightPath).ansMe;
    }
};

void solve()
{
    std::cin >> n;
    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> color[i];
    }

    HLD::build();

    std::cin >> q;
    for(int i = 1 ; i <= q ; ++i)
    {
        int type, x, y, z;
        std::cin >> type;

        if(type == 1)
        {
            std::cin >> x >> y >> z;
            HLD::updatePath(x, y, z);
        }
        else if(type == 2)
        {
            std::cin >> x >> y;
            HLD::updateSubtree(x, y);
        }
        else
        {
            std::cin >> x >> y;
            std::cout << HLD::query(x, y) << "\n";
        }
    }    
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
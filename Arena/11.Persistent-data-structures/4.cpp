#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

const int MAXN = 100000 + 10;
const int MAXLOG = 25;

int n, m;
int label[MAXN];
int compress[MAXN];
std::vector<int> g[MAXN];

struct PersistentSegmentTree
{
    struct Node
    {
        int sum;
        int left, right;

        Node()
        {
            sum = 0;
            left = right = 0;
        }

        void assign(const Node &left, const Node &right)
        {
            sum = left.sum + right.sum;
        }

        friend Node operator + (const Node &left, const Node &right)
        {
            Node res;
            res.sum = left.sum + right.sum;
            return res;
        }
    };

    struct RootNodes
    {
        int a;
        int b;
        int lca;
        int parLca;
    };

    Node tree[MAXN * MAXLOG];
    int cnt;

    void build(int node, int l, int r)
    {
        if(l == r)
        {
            tree[node].sum = 0;
            return;
        }

        int mid = l + r >> 1;
        tree[node].left = ++cnt;
        tree[node].right = ++cnt;
        build(tree[node].left, l, mid);
        build(tree[node].right, mid + 1, r);
    }

    void update(int newNode, int oldNode, int l, int r, int queryPos, int queryVal)
    {
        tree[newNode] = tree[oldNode];

        if(l == r)
        {
            tree[newNode].sum += queryVal;
            return;
        }

        int mid = l + r >> 1;
        if(queryPos <= mid)
        {
            tree[newNode].left = ++cnt;
            update(tree[newNode].left, tree[oldNode].left, l, mid, queryPos, queryVal);
        }
        else
        {
            tree[newNode].right = ++cnt;
            update(tree[newNode].right, tree[oldNode].right, mid + 1, r, queryPos, queryVal);
        }

        tree[newNode].assign(tree[tree[newNode].left], tree[tree[newNode].right]);
    }

    RootNodes left(RootNodes nodes)
    {
        RootNodes res;
        res.a = tree[nodes.a].left;
        res.b = tree[nodes.b].left;
        res.lca = tree[nodes.lca].left;
        res.parLca = tree[nodes.parLca].left;
        return res;
    }

    RootNodes right(RootNodes nodes)
    {
        RootNodes res;
        res.a = tree[nodes.a].right;
        res.b = tree[nodes.b].right;
        res.lca = tree[nodes.lca].right;
        res.parLca = tree[nodes.parLca].right;
        return res;
    }

    int leftSum(RootNodes nodes)
    {
        RootNodes res = left(nodes);
        return tree[res.a].sum + tree[res.b].sum - tree[res.lca].sum - tree[res.parLca].sum;
    }

    int descent(RootNodes nodes, int l, int r, int k)
    {
        if(l == r)
        {
            return l;
        }

        int mid = l + r >> 1;
        if(leftSum(nodes) >= k)
        {
            return descent(left(nodes), l, mid, k);
        }

        return descent(right(nodes), mid + 1, r, k - leftSum(nodes));
    }

    int build()
    {
        cnt = 1;
        build(1, 1, n);
        return 1;
    }

    int update(int oldRoot, int pos, int val)
    {
        int newRoot = ++cnt;
        update(newRoot, oldRoot, 1, n, pos, val);
        return newRoot;
    }

    int query(int a, int b, int lca, int parLca, int k)
    {
        return descent({a, b, lca, parLca}, 1, n, k);
    }
};

int timer;
int in[MAXN];
int out[MAXN];
int jump[MAXN][MAXLOG];
int root[MAXN];
PersistentSegmentTree tree;
std::unordered_map<int, int> map;
std::unordered_map<int, int> rev;

bool isAncestor(int u, int v)
{
    return in[u] <= in[v] && out[u] >= out[v];
}

int findLca(int u, int v)
{
    if(isAncestor(u, v)) return u;
    if(isAncestor(v, u)) return v;

    for(int lg = MAXLOG - 1 ; lg >= 0 ; --lg)
    {
        int next = jump[u][lg];

        if(next != 0 && !isAncestor(next, v))
        {
            u = next;
        }
    }

    return jump[u][0];
}

void dfs(int node, int par)
{
    in[node] = ++timer;

    root[node] = tree.update(root[par], map[label[node]], +1);

    jump[node][0] = par;
    for(int lg = 1 ; lg < MAXLOG ; ++lg)
    {
        jump[node][lg] = jump[jump[node][lg - 1]][lg - 1];
    }

    for(const int &to : g[node])
    {
        if(to == par) continue;
        dfs(to, node);
    }

    out[node] = timer;
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> label[i];
        compress[i] = label[i];
    }

    int value = 1;
    std::sort(compress + 1, compress + n + 1);
    for(int i = 1 ; i <= n ; ++i)
    {
        map[compress[i]] = value;
        rev[value] = compress[i];

        if(i != n && compress[i] != compress[i + 1])
        {
            value += 1;
        }
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    root[0] = tree.build();
    dfs(1, 0);

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, k;
        std::cin >> a >> b >> k;
        
        int lca = findLca(a, b);
        std::cout << rev[tree.query(root[a], root[b], root[lca], root[jump[lca][0]], k)] << "\n";
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
}
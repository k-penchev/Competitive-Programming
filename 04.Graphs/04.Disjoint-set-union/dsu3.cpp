#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

const int MAXN = 3 * 1e5 + 10;

int n, q;
int ans[MAXN];
std::vector<int> query;
std::map<std::pair<int, int>, int> my_map;

struct DSU
{
    struct Change
    {
        int xRoot;  // root that became child
        int yRoot;  // root that stayed parent
        int ySize;  // previous size[yRoot] before union
    };
    
    int parent[MAXN];
    int size[MAXN];
    std::vector<Change> history;
    int components;

    void set()
    {
        components = n;
        history.clear();
        for(int i = 1 ; i <= n ; ++i)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x)
    {
        if(parent[x] == x)
        {
            return x;
        }

        return find(parent[x]);
    }

    void connect(int x, int y)
    {
        x = find(x);
        y = find(y);

        if(x == y)
        {
            history.push_back({-1, -1, 0});
            return;
        }

        if(size[x] > size[y])
        {
            std::swap(x, y);
        }

        history.push_back({x, y, size[y]});

        parent[x] = y;
        size[y] += size[x];
        components -= 1;
    }

    bool areConnected(int x, int y)
    {
        return find(x) == find(y);
    }

    int getComponents()
    {
        return components;
    }

    int snapshot()
    {
        return history.size();
    }

    void undo()
    {
        if(history.empty()) return; 

        Change state = history.back();
        history.pop_back();

        if(state.xRoot == -1) return;

        int x = state.xRoot;
        int y = state.yRoot;

        parent[x] = x;
        size[y] = state.ySize;
        components += 1; 
    }

    void rollback(int snap)
    {
        while(history.size() > snap)
        {
            undo();
        }
    }
};

DSU dsu;

struct SegmentTree
{           
    struct Edge
    {
        int u;
        int v;
    };

    std::vector<Edge> tree[4 * MAXN];

    void update(int idx, int low, int high, int queryL, int queryR, int u, int v)
    {
        if(low > high) return;

        if(queryL > high || queryR < low)
        {
            return;
        }
        else if(queryL <= low && high <= queryR)
        {
            tree[idx].push_back({u, v});
            return;
        }

        int mid = (low + high) / 2;

        update(2 * idx, low, mid, queryL, queryR, u, v);
        update(2 * idx + 1, mid + 1, high, queryL, queryR, u, v);
    }

    void dfs(int idx, int low, int high)
    {
        if(low > high) return;

        int snap = dsu.snapshot();

        for(auto &[u, v] : tree[idx])
        {
            dsu.connect(u, v);
        }

        if(low == high)
        {
            ans[low] = dsu.getComponents();
            dsu.rollback(snap);
            return;
        }

        int mid = (low + high) / 2;

        dfs(2 * idx, low, mid);
        dfs(2 * idx + 1, mid + 1, high);

        dsu.rollback(snap);
    }

    void update(int l, int r, int u, int v)
    {
        update(1, 1, q, l, r, u, v);
    }

    void dfs()
    {
        dfs(1, 1, q);
    }
};

SegmentTree tree;

void solve()
{
    std::freopen("connect.in", "r", stdin);
    std::freopen("connect.out", "w", stdout);

    std::cin >> n >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        char type;
        int x, y;

        std::cin >> type;
        if(type == '+')
        {   
            std::cin >> x >> y;
            if(x > y) std::swap(x, y);
            my_map[{x, y}] = i;
        }
        else if(type == '-')
        {
            std::cin >> x >> y;
            if(x > y) std::swap(x, y);
            tree.update(my_map[{x, y}], i - 1, x, y);
            my_map.erase({x, y});
        }
        else
        {
            query.push_back(i);
        }
    }

    for(auto &[key, value] : my_map)
    {
        tree.update(value, q, key.first, key.second);
    }

    dsu.set();
    tree.dfs();

    int ptr = 0;
    for(int i = 1 ; i <= q ; ++i)
    {
        if(ptr < query.size() && query[ptr] == i)
        {
            std::cout << ans[i] << "\n";
            ptr += 1;
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
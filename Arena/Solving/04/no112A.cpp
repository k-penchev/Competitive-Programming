#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

const int MAXN = 1e3 + 10;
const int MAXQ = 1e5 + 100;

int n, m, q;
std::map<std::pair<int, int>, int> map;
std::vector<int> queryPos;
std::pair<int, int> query[MAXQ];
bool ans[MAXQ];

struct DSU
{
    struct Change
    {
        int xRoot;
        int yRoot;
        int ySize;
    };

    int parent[MAXN];
    int size[MAXN];
    std::vector<Change> history;

    void set()
    {
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
            history.push_back({-1, -1, -1});
            return;
        }

        if(size[x] > size[y])
        {
            std::swap(x, y);
        }

        history.push_back({x, y, size[y]});
        parent[x] = y;
        size[y] += size[x];
    }

    bool areConnected(int x, int y)
    {
        return find(x) == find(y); 
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

        parent[state.xRoot] = state.xRoot;
        size[state.yRoot] = state.ySize;
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

    std::vector<Edge> tree[4 * MAXQ];
    
    void addEdge(int idx, int low, int high, int queryL, int queryR, int u, int v)
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
        addEdge(2 * idx, low, mid, queryL, queryR, u, v);
        addEdge(2 * idx + 1, mid + 1, high, queryL, queryR, u, v);
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
            if(query[low].first != 0)
            {
                ans[low] = dsu.areConnected(query[low].first, query[low].second);
            }

            dsu.rollback(snap);
            return;
        }

        int mid = (low + high) / 2;
        dfs(2 * idx, low, mid);
        dfs(2 * idx + 1, mid + 1, high);

        dsu.rollback(snap);
    }

    void addEdge(int l, int r, int u, int v)
    {
        addEdge(1, 1, q, l, r, u, v);
    }

    void dfs()
    {
        dfs(1, 1, q);
    }
};

SegmentTree tree;

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        if(a > b) std::swap(a, b);
        map[{a, b}] = 1;
    }

    std::cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        int type, a, b;
        std::cin >> type >> a >> b;
        if(a > b) std::swap(a, b);

        if(type == 1)
        {
            queryPos.push_back(i);
            query[i] = {a, b};
        }
        else if(type == 2)
        {
            if(!map.count({a, b}))
            {
                map[{a, b}] = i;
            }
        }
        else
        {
            if(!map.count({a, b}))
            {
                continue;
            }

            tree.addEdge(map[{a, b}], i - 1, a, b);
            map.erase({a, b});
        }
    }

    for(auto &[key, value] : map)
    {
        tree.addEdge(value, q, key.first, key.second);
    }

    dsu.set();
    tree.dfs();

    int ptr = 0;
    for(int i = 1 ; i <= q ; ++i)
    {
        if(ptr < queryPos.size() && queryPos[ptr] == i)
        {
            ptr += 1;
            std::cout << ans[i];
        }
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
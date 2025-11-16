#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 2 * 1e5 + 10;

int n, m;

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

        // !!without path compression
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
    }

    bool areConnected(int x, int y)
    {
        return find(x) == find(y);
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
    }

    int snapshot()
    {
        return history.size();
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

void solve()
{
    std::cin >> n >> m;
    dsu.set();
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
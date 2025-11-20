//the graph is dynamic (new edges are being added)
//https://www.spoj.com/problems/ONBRIDGE/
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

const int MAXN = 50000 + 10;

int t, n, m;
int treePar[MAXN]; 

struct DSU
{
    int size[MAXN];
    int par[MAXN];

    void build()
    {
        std::fill(size + 1, size + n + 1, 1);
        std::iota(par + 1, par + n + 1, 1);
    }

    int find(int x)
    {
        if(par[x] == x)
        {
            return x;
        }

        return par[x] = find(par[x]);
    }

    void connect(int x, int y)
    {
        x = find(x);
        y = find(y);

        if(x == y)
        {
            return;
        }

        if(size[x] > size[y])
        {
            std::swap(x, y);
        }

        par[x] = y;
        size[y] += size[x];
    }

    bool areConnected(int x, int y)
    {
        return find(x) == find(y);
    }
};

DSU bcc;
DSU comp;
int bridges = 0;
int lastVisit[MAXN];
int lcaIteration = 0;

void mergePath(int x, int y)
{
    x = bcc.find(x);
    y = bcc.find(y);

    std::vector<int> xSide;
    std::vector<int> ySide;

    ++lcaIteration;

    int lca = -1;
    while(lca == -1)
    {
        if(x != -1)
        {
            x = bcc.find(x);
            xSide.push_back(x);

            if(lastVisit[x] == lcaIteration)
            {
                lca = x;
                break;
            }

            lastVisit[x] = lcaIteration;
            x = treePar[x];
        }

        if(y != -1)
        {
            y = bcc.find(y);
            ySide.push_back(y);

            if(lastVisit[y] == lcaIteration)
            {
                lca = y;
                break;
            }

            lastVisit[y] = lcaIteration;
            y = treePar[y];
        }
    }

    for(int v : xSide)
    {
        v = bcc.find(v);
        bcc.par[v] = lca;

        if(v == lca)
        {
            break;
        }

        --bridges;
    }

    for(int v : ySide)
    {
        v = bcc.find(v);
        bcc.par[v] = lca;

        if(v == lca)
        {
            break;
        }

        --bridges;
    }
}

void makeRoot(int newRoot)
{
    int root = newRoot;
    int child = -1;

    int v = newRoot;
    while(v != -1)
    {
        int p = treePar[v];

        if(p != -1)
        {
            p = bcc.find(p);
        }

        treePar[v] = child;
        comp.par[v] = root;

        child = v;
        v = p;
    }

    comp.size[root] = comp.size[child];
}

void addEdge(int x, int y)
{
    x = bcc.find(x);
    y = bcc.find(y);

    if(x == y)
    {
        return;
    }

    int u = comp.find(x);
    int v = comp.find(y);

    if(u != v)
    {
        bridges += 1;

        if(comp.size[u] > comp.size[v])
        {
            std::swap(x, y);
            std::swap(u, v);
        }  

        makeRoot(x);
        comp.connect(x, y);
        treePar[x] = y;
    }
    else
    {
        mergePath(x, y);
    }
}

void reset()
{
    bcc.build();
    comp.build();
    
    bridges = 0;
    lcaIteration = 0;    
    for(int i = 1; i <= n; ++i)
    {
        treePar[i] = -1;
        lastVisit[i] = 0;
    }
}

void solve()
{
    std::cin >> t;

    for(int test = 1 ; test <= t ; ++test)
    {
        std::cin >> n >> m;

        reset();
        for(int i = 1 ; i <= m ; ++i)
        {
            int u, v;
            std::cin >> u >> v;
            u += 1, v += 1;

            addEdge(u, v);
            std::cout << bridges << "\n";
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
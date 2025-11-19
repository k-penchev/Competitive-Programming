#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

const int MAXN = 1e5 + 5;
const int MAXM = 500000 + 5;

int n, m, q;

struct Edge
{
    int from;
    int to;
    int idx;
};

std::vector<Edge> edge;
std::vector<Edge> g[MAXN];
std::vector<Edge> tree[MAXN];
std::map<std::pair<int, int>, int> map;

bool visited[MAXN];

int timer = 1;
int in[MAXN], low[MAXN];
bool isBridge[MAXM];

int counter = 1;
int component[MAXN];

int parent[MAXN];
int depth[MAXN];

void findBridges(int node, int par)
{
    visited[node] = 1;
    in[node] = low[node] = timer++;
    
    for(auto &[from, to, idx] : g[node])
    {
        if(to == par)
        {
            continue;
        }

        if(visited[to])
        {
            low[node] = std::min(low[node], in[to]);
        }
        else
        {
            findBridges(to, node);
            low[node] = std::min(low[node], low[to]);

            if(low[to] > in[node])
            {
                isBridge[idx] = 1;
            }
        }
    }
}

void findBCC(int node)
{
    visited[node] = 1;
    component[node] = counter;

    for(auto &[from, to, idx] : g[node])
    {
        if(isBridge[idx])
        {
            continue;
        }

        if(!visited[to])
        {
            findBCC(to);
        }
    }
}

void dfs(int node, int par, int dep)
{
    parent[node] = par;
    depth[node] = dep;

    for(auto &[from, to, idx] : tree[node])
    {
        if(to == par)
        {
            continue;
        }

        dfs(to, node, dep + 1);
    }
}

void check(int &u, int &v)
{
    if(u > v)
    {
        std::swap(u, v);
    }
}

bool lift(int &node, int banned)
{
    int l = node;
    int r = parent[node];
    check(l, r);

    if(map[{l, r}] == banned)
    {
        return false;
    }

    node = parent[node];
    return true;
}

bool queryEdge(int x, int y, int a, int b)
{
    int ca = component[a];
    int cb = component[b];
    check(ca, cb);

    int banned = map[{ca, cb}];

    x = component[x];
    y = component[y];

    if(!isBridge[banned] || x == y)
    {
        return true;
    }

    if(depth[x] > depth[y])
    {
        std::swap(x, y);
    }

    while(depth[x] != depth[y])
    {
        if(!lift(y, banned))
        {
            return false;
        }
    }

    while(x != y)
    {
        if(!lift(x, banned))
        {
            return false;
        }

        if(!lift(y, banned))
        {
            return false;
        }
    }

    return true;
}

bool queryNode(int x, int y, int a)
{
    //not implemented
    return true;
}

void solve()
{
    std::cin >> n >> m;
    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        check(a, b);

        edge.push_back({a, b, i});
        g[a].push_back({-1, b, i});
        g[b].push_back({-1, a, i});
    }

    findBridges(1, -1);

    std::fill(visited + 1, visited + n + 1, false);
    for(int i = 1 ; i <= n ; ++i)
    {
        if(!visited[i])
        {
            findBCC(i);
            counter += 1;
        }
    }

    for(int i = 0 ; i < m ; ++i)
    {
        int idx = edge[i].idx; 
        if(isBridge[idx])
        {
            
            int u = component[edge[i].from];
            int v = component[edge[i].to];
            check(u, v);
            
            tree[u].push_back({-1, v, idx});
            tree[v].push_back({-1, u, idx});
            map[{u, v}] = idx;
        }
    }
    
    dfs(1, -1, 0);

    std::cin >> q;
    for(int i = 1 ; i <= q; ++i)
    {
        int type, x, y, a, b;

        std::cin >> type;
        if(type == 1)
        {
            std::cin >> x >> y >> a >> b;
            check(a, b);
            std::cout << (queryEdge(x, y, a, b) ? "yes" : "no") << "\n";
        }
        else
        {
            std::cin >> x >> y >> a;
            std::cout << (queryNode(x, y, a) ? "yes" : "no") << "\n";
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
}
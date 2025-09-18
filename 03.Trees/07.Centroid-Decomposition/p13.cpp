#include <iostream>
#include <vector>

#define int long long

const int MAXN = 3 * 1e5 + 10;
const int MAXLOG = 20 + 1;
const int INF = 1e9;

int n, k;
std::vector<int> tree[MAXN];
int shop[MAXN], f[MAXN], p[MAXN];
int shopDist[MAXN], favDist[MAXN];

namespace LCA
{
    int in[MAXN], out[MAXN], timer = 0;
    int up[MAXN][MAXLOG], depth[MAXN];

    void dfs(int node, int par, int currDepth)
    {
        in[node] = ++timer;
        depth[node] = currDepth;
        up[node][0] = par;

        for(int i = 1 ; i < MAXLOG ; ++i)
        {
            int prev = up[node][i - 1];
            up[node][i] = up[prev][i - 1];
        }

        for(const int& child : tree[node])
        {
            if(child == par) continue;
            dfs(child, node, currDepth + 1);
        }

        out[node] = timer;
    }

    void build()
    {
        dfs(1, 0, 0);
    }

    bool is_ancestor(int a, int b)
    {
        return (in[a] <= in[b] && out[a] >= out[b]);
    }

    int lca(int a, int b)
    {
        if(is_ancestor(a, b)) return a;
        if(is_ancestor(b, a)) return b;

        for(int i = MAXLOG - 1 ; i >= 0 ; --i)
        {
            int anc = up[a][i];
            if(anc != 0 && !is_ancestor(anc, b)) a = anc;
        }

        return up[a][0];
    }

    int dist(int a, int b)
    {
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }
};

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    int centroidPar[MAXN][MAXLOG];
    int centroidDist[MAXN][MAXLOG];

    std::vector<int> centroidRadius[MAXN];
    std::vector<int> childRadius[MAXN];

    void findSize(int node, int par)
    {
        sz[node] = 1;

        for(const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;
            findSize(child, node);
            sz[node] += sz[child];
        }
    }

    int findCentroid(int node, int par, int globalSize)
    {
        for(const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;
            if(sz[child] * 2 > globalSize) return findCentroid(child, node, globalSize);
        }
        return node;
    }

    void stampLevel(int node, int par, int centroid, int currDist, int level)
    {
        centroidPar[node][level] = centroid;
        centroidDist[node][level] = currDist;

        for(const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;
            stampLevel(child, node, centroid, currDist + 1, level);
        }
    }

    void decompose(int node, int level)
    {
        findSize(node, 0);
        int cntr = findCentroid(node, 0, sz[node]);

        vis[cntr] = 1;

        stampLevel(cntr, 0, cntr, 0, level);

        // size by component size (safe bound)
        centroidRadius[cntr].assign(sz[cntr], 0);
        childRadius[cntr].assign(sz[cntr] + 1, 0);

        for(const int& child : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child, level + 1);
        }
    }

    void build()
    {
        decompose(1, 0);
    }

    void update(int node, int radius)
    {
        if(radius < 0) return;

        int prev = -1;
        for(int level = 0 ; level < MAXLOG ; ++level)
        {
            int cntr = centroidPar[node][level];
            if(cntr == 0) break;

            int d = centroidDist[node][level];
            int rem = radius - d;
            if(rem >= 0)
            {
                int i1 = rem;
                if(i1 >= (int)centroidRadius[cntr].size()) i1 = (int)centroidRadius[cntr].size() - 1;
                if(i1 >= 0) centroidRadius[cntr][i1] += 1;

                if(prev != -1)
                {
                    int i2 = rem;
                    if(i2 >= (int)childRadius[prev].size()) i2 = (int)childRadius[prev].size() - 1;
                    if(i2 >= 0) childRadius[prev][i2] += 1;
                }
            }

            prev = cntr;
        }
    }

    void propagate()
    {
        for(int c = 1 ; c <= n ; ++c)
        {
            if(!centroidRadius[c].empty())
            {
                for(int j = (int)centroidRadius[c].size() - 2 ; j >= 0 ; --j)
                {
                    centroidRadius[c][j] += centroidRadius[c][j + 1];
                }
            }
            if(!childRadius[c].empty())
            {
                for(int j = (int)childRadius[c].size() - 2 ; j >= 0 ; --j)
                {
                    childRadius[c][j] += childRadius[c][j + 1];
                }
            }
        }
    }

    int query(int node)
    {
        int s = 0;
        int prevCntr = -1;

        for(int level = 0 ; level < MAXLOG ; ++level)
        {
            int cntr = centroidPar[node][level];
            if(cntr == 0) break;

            int d = centroidDist[node][level];

            if(!centroidRadius[cntr].empty())
            {
                int idx = d;
                if(idx >= (int)centroidRadius[cntr].size()) idx = (int)centroidRadius[cntr].size() - 1;
                s += centroidRadius[cntr][idx];
            }

            if(prevCntr != -1 && !childRadius[prevCntr].empty())
            {
                int idx2 = d;
                if(idx2 >= (int)childRadius[prevCntr].size()) idx2 = (int)childRadius[prevCntr].size() - 1;
                s -= childRadius[prevCntr][idx2];
            }

            prevCntr = cntr;
        }

        return s;
    }
};

void dfs1(int node, int par)
{
    for(const int& child : tree[node])
    {
        if(child == par) continue;
        dfs1(child, node);
        shopDist[node] = std::min(shopDist[node], shopDist[child] + 1);
    }
}

void dfs2(int node, int par)
{
    for(const int& child : tree[node])
    {
        if(child == par) continue;
        shopDist[child] = std::min(shopDist[child], shopDist[node] + 1);
        dfs2(child, node);
    }
}

void solve()
{
    std::fill(shopDist + 1, shopDist + n + 1, INF);
    for(int i = 1 ; i <= k ; ++i) shopDist[shop[i]] = 0;

    dfs1(1, 0);
    dfs2(1, 0);

    LCA::build();
    Centroid::build();

    for(int i = 1 ; i <= n ; ++i) favDist[i] = LCA::dist(i, f[i]);

    for(int i = 1 ; i <= n ; ++i)
    {
        int radius = std::min(shopDist[i], favDist[i] - p[i] - 1);
        Centroid::update(i, radius);
    }

    Centroid::propagate();

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << Centroid::query(i) << " ";
    }
    std::cout << "\n";
}

void input()
{
    std::cin >> n >> k;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    for(int i = 1 ; i <= k ; ++i) std::cin >> shop[i];
    for(int i = 1 ; i <= n ; ++i) std::cin >> f[i] >> p[i];
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
    input();
    solve();
}

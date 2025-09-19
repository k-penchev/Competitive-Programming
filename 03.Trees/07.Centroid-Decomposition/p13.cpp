#include <iostream>
#include <vector>

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

    void tour(int node, int par, int currDepth)
    {
        in[node] = ++timer;
        depth[node] = currDepth;
        up[node][0] = par;

        for (int i = 1 ; i < MAXLOG ; ++i)
        {
            int prev = up[node][i - 1];
            up[node][i] = up[prev][i - 1];
        }

        for (const int& child : tree[node])
        {
            if(child == par) continue;
            tour(child, node, currDepth + 1);
        }

        out[node] = timer;
    }

    void build()
    {
        tour(1, 0, 0);
    }

    bool is_anc(int a, int b)
    {
        return (in[a] <= in[b] && out[a] >= out[b]);
    }

    int lca(int a, int b)
    {
        if(is_anc(a, b)) return a;
        if(is_anc(b, a)) return b;

        for (int i = MAXLOG - 1 ; i >= 0 ; --i)
        {
            int nxt = up[a][i];

            if (nxt != 0 && !is_anc(nxt, b))
            {
                a = nxt;
            }
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
    std::vector<int> centroidRadius[MAXN];  // the centroid values itself
    std::vector<int> childRadius[MAXN];     // the values for the parentCentroid 

    void findSize(int node, int par)
    {
        sz[node] = 1;

        for (const int& child : tree[node])
        {
            if (child == par || vis[child]) continue;

            findSize(child, node);
            sz[node] += sz[child];
        }
    }

    int findCentroid(int node, int par, int globalSize)
    {
        for (const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;

            if(sz[child] * 2 > globalSize) return findCentroid(child, node, globalSize);
        }

        return node;
    }

    void calculateDist(int node, int par, int currDist, int globalCentroid, int globalLevel)
    {
        centroidPar[node][globalLevel] = globalCentroid;
        centroidDist[node][globalLevel] = currDist;

        for (const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;
            calculateDist(child, node, currDist + 1, globalCentroid, globalLevel);
        }
    }

    void decompose(int node, int lvl)
    {
        findSize(node, 0);
        int cntr = findCentroid(node, 0, sz[node]);

        vis[cntr] = 1;
        calculateDist(cntr, 0, 0, cntr, lvl);
        
        centroidRadius[cntr].resize(sz[node]);
        childRadius[cntr].resize(sz[node] + 1);

        for (const int& child : tree[cntr])
        {
            if (vis[child]) continue;
            decompose(child, lvl + 1);
        }
    }

    void build()
    {
        decompose(1, 0);
    }

    void propagate()
    {
        for (int i = 1 ; i <= n ; ++i)
        {
            int m = centroidRadius[i].size();

            for (int j = m - 2 ; j >= 0 ; --j)
            {
                centroidRadius[i][j] += centroidRadius[i][j + 1];
            }

            m = childRadius[i].size();

            for (int j = m - 2 ; j >= 0 ; --j)
            {
                childRadius[i][j] += childRadius[i][j + 1];
            }
        }
        
    }

    void update(int node, int R)
    {
        if (R < 0) return;
        
        int prev = -1;
        
        for (int lvl = 0; lvl < MAXLOG; ++lvl)
        {            
            int cntr = centroidPar[node][lvl];
            
            if (cntr == 0) break;                                     
            
            int d = centroidDist[node][lvl];
            int raw = R - d;
            
            if (raw < 0) continue;

            int idxC = std::min(raw, (int)centroidRadius[cntr].size() - 1);
            centroidRadius[cntr][idxC] += 1;

            if (prev != -1)
            {
                int idxP = std::min(raw, (int)childRadius[prev].size() - 1);
                childRadius[prev][idxP] += 1;
            }
            prev = cntr;

        }
    }


    int query(int node)
    {
        int s = 0, prev = -1;
        
        for (int lvl = 0; lvl < MAXLOG; ++lvl)
        {
            int cntr = centroidPar[node][lvl];
            
            if (cntr == 0) break;
            
            int d = centroidDist[node][lvl];
            
            if (d < (int)centroidRadius[cntr].size()) s += centroidRadius[cntr][d];
            if (prev != -1 && d < (int)childRadius[prev].size()) s -= childRadius[prev][d];
            
            prev = cntr;
        }
        
        return s;
    }

};

void dfs1(int node, int par)
{
    for (const int& child : tree[node])
    {
        if (child == par) continue;

        dfs1(child, node);
        shopDist[node] = std::min(shopDist[node], shopDist[child] + 1);
    }
}

void dfs2(int node, int par)
{
    for (const int& child : tree[node])
    {
        if (child == par) continue;

        shopDist[child] = std::min(shopDist[child], shopDist[node] + 1);
        dfs2(child, node);
    }
}

void solve()
{
    std::fill(shopDist + 1, shopDist + n + 1, INF);
    for (int i = 1 ; i <= k ; ++i)
    {
        shopDist[shop[i]] = 0;
    }

    dfs1(1, 0);
    dfs2(1, 0);

    LCA::build();
    Centroid::build();

    for (int i = 1 ; i <= n ; ++i)
    {
        favDist[i] = LCA::dist(i, f[i]);
    }

    for (int i = 1 ; i <= n ; ++i)
    {
        if (favDist[i] <= shopDist[i] + p[i])
        {
            Centroid::update(i, favDist[i] - p[i] - 1);
        }
        else
        {
            Centroid::update(i, shopDist[i]);
        }
        
    }

    Centroid::propagate();

    for (int i = 1 ; i <= n ; ++i)
    {
        std::cout << Centroid::query(i) << " ";
    }

    std::cout << "\n";
}

void input()
{
    std::cin >> n >> k;

    for (int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; 
        std::cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    for (int i = 1 ; i <= k ; ++i)
    {
        std::cin >> shop[i];
    }

    for (int i = 1 ; i <= n ; ++i)
    {
        std::cin >> f[i] >> p[i];
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
    input();
    solve();
}
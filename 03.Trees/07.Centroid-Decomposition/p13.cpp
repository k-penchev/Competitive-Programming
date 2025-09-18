#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 3 * 1e5 + 10;
const int INF = 1e9;
const int MAXLOG = 20 + 1;

int n, k;
std::vector<int> tree[MAXN];
int shop[MAXN], f[MAXN], p[MAXN];

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    int centroidPar[MAXN][MAXLOG];
    int centroidDist[MAXN][MAXLOG];
    int shopDist[MAXN], bobDist[MAXN];

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
            if (child == par || vis[child]) continue;

            if (sz[child] * 2 > globalSize) return findCentroid(child, node, globalSize);
        }
        
        return node;
    }

    void computeDist(int node, int par, int currDist, int centroid, int level)
    {
        centroidPar[node][level] = centroid;
        centroidDist[node][level] = currDist;

        for (const int& child : tree[node])
        {
            if (child == par || vis[child]) continue;
            computeDist(child, node, currDist + 1, centroid, level);
        }
    }


    void decompose(int node, int lvl)
    {
        findSize(node, -1);
        int cntr = findCentroid(node, -1, sz[node]);

        vis[cntr] = 1;

        computeDist(cntr, -1, 0, cntr, lvl);

        for (const int& child : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child, lvl + 1);
        }
    }

    void build()
    {
        std::fill(shopDist + 1, shopDist + n + 1, INF);
        std::fill(bobDist + 1, bobDist + n + 1, INF);
        decompose(1, -1);
    }

    void update1(int node)
    {
        for (int lvl = 0 ; lvl < MAXLOG ; ++lvl)
        {
            int cntr = centroidPar[node][lvl];
            int dist = centroidDist[node][lvl];

            if(cntr == 0) break;

            shopDist[cntr] = std::min(shopDist[cntr], dist);
        }
    }

    void update2(int node)
    {
        for (int lvl = 0 ; lvl < MAXLOG ; ++lvl)
        {
            int cntr = centroidPar[node][lvl];
            int dist = centroidDist[node][lvl];
            int closestShopDist = shopDist[cntr];

            if(cntr == 0) break;

            bobDist[cntr] = std::min(bobDist[cntr], dist);
        }
    }

};

void solve()
{
    Centroid::build();

    for (int i = 1 ; i <= k ; ++i)
    {
        Centroid::update1(shop[i]);
    }

    for (int i = 1 ; i <= n ; ++i)
    {
        Centroid::update2(i);
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
    
    return 0;
}
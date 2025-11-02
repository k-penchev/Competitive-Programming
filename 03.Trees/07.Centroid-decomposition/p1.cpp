#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXLOG = 20;
const int INF = 1e9;

int n, m;
vector<int> tree[MAXN];

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    int best[MAXN];
    int centroidPar[MAXN][MAXLOG];
    int centroidDist[MAXN][MAXLOG];

    void findSize(int node, int par)
    {
        sz[node] = 1;

        for(const int& child : tree[node])
        {
            if(child == par || vis[child]) 
            {
                continue;
            }

            findSize(child, node);
            sz[node] += sz[child];
        }
    }

    int findCentroid(int node, int par, int globalSize)
    {
        for(const int& child : tree[node])
        {
            if(child == par || vis[child])
            {
                continue;
            }

            if(sz[child] * 2 > globalSize)
            {
                return findCentroid(child, node, globalSize);
            }
        }

        return node;
    }

    void computeDistance(int node, int par, int level, int dist, int globalCentroid)
    {
        centroidPar[node][level] = globalCentroid;
        centroidDist[node][level] = dist;

        for(const int& child : tree[node])
        {
            if(child == par || vis[child])
            {
                continue;
            }

            computeDistance(child, node, level, dist + 1, globalCentroid);
        }
    }

    void decompose(int node, int level)
    {
        findSize(node, 0);
        int cntr = findCentroid(node, 0, sz[node]);

        vis[cntr] = true;
        computeDistance(cntr, 0, level, 0, cntr);

        for(const int& child : tree[cntr])
        {
            if(vis[child])
            {
                continue;
            }

            decompose(child, level + 1);
        }
    }

    void build()
    {
        decompose(1, 0);
        fill(best, best + MAXN, INF);
        fill(vis, vis + MAXN, false);
    }

    void update(int node)
    {
        for(int level = 0 ; level < MAXLOG ; ++level)
        {
            int c = centroidPar[node][level];
            
            if(c == 0)
            {
                break;
            }
            
            best[c] = min(best[c], centroidDist[node][level]);
        }
    }

    int query(int node)
    {
        int res = INF;

        for(int level = 0 ; level < MAXLOG ; ++level)
        {
            int c = centroidPar[node][level];

            if(c == 0)
            {
                break;
            }

            res = min(res, best[c] + centroidDist[node][level]);
        }

        return res;
    }
};

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; 
        cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    Centroid::build();
    Centroid::update(1);

    for(int i = 1 ; i <= m ; ++i)
    {
        int qType, node;
        cin >> qType >> node;

        if(qType == 1)
        {
            Centroid::update(node);
        }
        else
        {
            cout << Centroid::query(node) << "\n";
        }
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
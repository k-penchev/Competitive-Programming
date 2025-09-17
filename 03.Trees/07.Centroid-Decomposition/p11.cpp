//#include "factories.h"
#include <iostream>
#include <vector>
#include <algorithm>

#define llong long long

const int MAXN = 5 * 1e5 + 10;
const int MAXLOG = 20 + 1;
const llong INF = 1e9 + 10;
const llong MAXW = MAXN * INF;

int n;
std::vector<std::pair<int, int>> tree[MAXN];
llong globalAns;

namespace Centroid
{
    llong sz[MAXN];
    bool vis[MAXN];
    llong centroidPar[MAXN][MAXLOG];
    llong centroidDist[MAXN][MAXLOG];
    llong best[MAXN];

    void findSize(int node, int par)
    {
        sz[node] = 1;

        for(const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;

            findSize(child, node);
            sz[node] += sz[child];
        }
    }

    int findCentroid(int node, int par, int globalSize)
    {
        for(const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;

            if(sz[child] * 2 > globalSize) return findCentroid(child, node, globalSize);
        }

        return node;
    }

    void calculateDist(int node, int par, int centroid, llong currDist, int level)
    {
        centroidPar[node][level] = centroid;
        centroidDist[node][level] = currDist;

        for(const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;
            calculateDist(child, node, centroid, currDist + w, level);
        }
    }

    void decompose(int node, int level)
    {
        findSize(node, -1);
        int cntr = findCentroid(node, -1, sz[node]);

        vis[cntr] = 1;
        calculateDist(cntr, -1, cntr, 0, level);

        for(const auto& [child, w] : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child, level + 1);
        }
    }

    void build()
    {
        std::fill(best, best + MAXN, MAXW);
        decompose(1, 0);
    }

    void setNode(int node)
    {
        for(int level = 0 ; level < MAXLOG ; ++level)
        {
            llong cntr = centroidPar[node][level];
            
            if(cntr == 0)
            {
                break;
            }

            best[cntr] = MAXW;
        }
    }

    void set(int S, int X[], int T, int Y[])
    {
        for(int i = 0 ; i < S ; ++i)
        {
            setNode(X[i] + 1);
        }

        for(int i = 0 ; i < T ; ++i)
        {
            setNode(Y[i] + 1);
        }

        globalAns = MAXW;
    }

    void putColor(int node, int clr)
    {
        for(int level = 0 ; level < MAXLOG ; ++level)
        {
            llong cntr = centroidPar[node][level];
            llong dist = centroidDist[node][level];

            if(cntr == 0)
            {
                break;
            }

            if(clr == 1)
            {
                best[cntr] = std::min(best[cntr], dist);
            }
            else
            {
                globalAns = std::min(globalAns, best[cntr] + dist);
            }
        }
    }
};

void Init(int N, int A[], int B[], int D[])
{
    n = N;

    for(int i = 0 ; i < n - 1 ; ++i)
    {
        tree[A[i] + 1].push_back({B[i] + 1, D[i]});
        tree[B[i] + 1].push_back({A[i] + 1, D[i]});
    }

    Centroid::build();
}

long long Query(int S, int X[], int T, int Y[])
{
    Centroid::set(S, X, T, Y);

    for(int i = 0 ; i < S ; ++i)
    {
        Centroid::putColor(X[i] + 1, 1);
    }

    for(int i = 0 ; i < T ; ++i)
    {
        Centroid::putColor(Y[i] + 1, 2);
    }

    return globalAns;
}

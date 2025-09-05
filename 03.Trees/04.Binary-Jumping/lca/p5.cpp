#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXQ = 2 * 1e5 + 10;
const int MAXLOG = 20 + 1;

int q;
int depth[MAXQ];
int lift[MAXQ][MAXLOG];
int nodesCnt = 0;
int root[MAXQ], A[MAXQ], B[MAXQ], diameter[MAXQ];

int lca(int a, int b)
{
    if(depth[a] < depth[b]) swap(a, b);

    int k = depth[a] - depth[b];

    for(int i = 0 ; i < MAXLOG ; ++i)
    {
        if(k & (1 << i))
        {
            a = lift[a][i];
        }
    }

    if(a == b)
    {
        return a;
    }

    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        if(lift[a][i] != lift[b][i])
        {
            a = lift[a][i];
            b = lift[b][i];
        }
    }
    
    return lift[a][0];
}

int dist(int a, int b)
{
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

void update(int par)
{
    nodesCnt++;

    int currentNode = nodesCnt;

    if(par == -1)
    {
        root[currentNode] = currentNode;
        A[currentNode] = B[currentNode] = root[currentNode];
        diameter[currentNode] = 0;

        for(int i = 0 ; i < MAXLOG ; ++i)
        {
            lift[currentNode][i] = 0;
        }

        depth[currentNode] = 0;
    }
    else
    {
        lift[currentNode][0] = par;

        for(int i = 1 ; i < MAXLOG ; ++i)
        {
            int prev = lift[currentNode][i - 1];
            lift[currentNode][i] = lift[prev][i - 1];
        }

        depth[currentNode] = depth[par] + 1;
        root[currentNode] = root[par];

        int componentRoot = root[currentNode];

        int dist1 = dist(currentNode, A[componentRoot]);
        int dist2 = dist(currentNode, B[componentRoot]);

        if(dist1 > diameter[componentRoot])
        {
            B[componentRoot] = currentNode;
            diameter[componentRoot] = dist1;
        }
        else if(dist2 > diameter[componentRoot])
        {
            A[componentRoot] = currentNode;
            diameter[componentRoot] = dist2;
        }
    }
}

int query(int node)
{
    int componenentRoot = root[node];
    return max(dist(node, A[componenentRoot]), dist(node, B[componenentRoot]));
}

void solve()
{
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);

    cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        char qType;
        int x;

        cin >> qType >> x;

        if(qType == 'B')
        {
            update(x);
        }
        else
        {
            cout << query(x) << "\n";
        }
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
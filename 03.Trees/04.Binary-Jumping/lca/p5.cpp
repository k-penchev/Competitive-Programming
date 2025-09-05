#include <bits/stdc++.h>

using namespace std;

const int MAXQ = 1e5 + 10;
const int MAXLOG = 17 + 1;

int q;
int depth[MAXQ];
int lift[MAXQ][MAXLOG];
int nodesCnt = 0;

int lca(int a, int b)
{

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
    }
}

int query(int node)
{

}

void solve()
{
    cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        char qType;
        int x;

        cin >> qType >> x;

        if(qType == 'B')
        {

        }
        else
        {

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
    
    return 0;
}
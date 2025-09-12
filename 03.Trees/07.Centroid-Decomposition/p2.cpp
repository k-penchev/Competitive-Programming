#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXLOG = 20;

int n;
vector<int> tree[MAXN];

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    char letter[MAXN];

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

    int getCentroid(int node, int par, int globalSize)
    {
        for (const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;

            if (sz[child] * 2 > globalSize) return getCentroid(child, node, globalSize);
        }

        return node;
    }

    void decompose(int node, char l)
    {
        findSize(node, 0);
        int centr = getCentroid(node, 0, sz[node]);

        vis[centr] = true;
        letter[centr] = l;

        for (const int& child : tree[centr])
        {
            if (vis[child]) continue;
            decompose(child, l + 1);
        }
    }

    void build()
    {
        decompose(1, 'A');
    }

    void print()
    {
        for (int i = 1 ; i <= n ; ++i)
        {
            cout << letter[i] << " ";
        }

        cout << "\n";
    }
};

void solve()
{
    cin >> n;

    for (int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    Centroid::build();
    Centroid::print();
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
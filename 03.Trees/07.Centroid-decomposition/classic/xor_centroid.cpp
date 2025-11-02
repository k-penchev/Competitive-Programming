#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXLOG = 21;

int n;
int val[MAXN];
vector<int> tree[MAXN];
long long ans = 0;

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    int cnt0[MAXLOG], cnt1[MAXLOG];

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

    void dfs(int node, int par, int currDist, int cntr, bool filling)
    {
        int d = currDist ^ val[node]; 

        if(filling)
        {
            for(int i = 0 ; i < MAXLOG ; ++i)
            {
                if(d & (1LL << i))
                {
                    cnt1[i] += 1;
                }
                else
                {
                    cnt0[i] += 1;
                }
            }
        }
        else
        {
            for (int i = 0; i < MAXLOG; ++i)
            {
                int x = (d >> i) & 1;                 
                int b = (val[cntr] >> i) & 1;         

                if (b == 0)
                {
                    ans += (1LL << i) * (x ? cnt0[i] : cnt1[i]);
                }
                else
                {
                    ans += (1LL << i) * (x ? cnt1[i] : cnt0[i]);
                }
            }
        }


        for(const int& child : tree[node])
        {
            if(child == par || vis[child]) continue;
            dfs(child, node, d, cntr, filling);
        }
    }

    void decompose(int node)
    {
        findSize(node, 0);
        int cntr = findCentroid(node, 0, sz[node]);

        vis[cntr] = 1;
        ans += val[cntr];

        for (int i = 0; i < MAXLOG; ++i)
            ((val[cntr] >> i) & 1) ? ++cnt1[i] : ++cnt0[i];

        for(const int& child : tree[cntr])
        {
            if(vis[child]) continue;

            dfs(child, cntr, val[cntr], cntr, false); 
            dfs(child, cntr, val[cntr], cntr, true);   

        }

        fill(cnt0, cnt0 + MAXLOG, 0);
        fill(cnt1, cnt1 + MAXLOG, 0);

        for(const int& child : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child);
        }
    }

    void build()
    {
        decompose(1);
    }
};

void solve()
{
    cin >> n;

    for (int i = 1 ; i <= n ; ++i)
    {
        cin >> val[i];
    }

    for (int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    Centroid::build();
    cout << ans << "\n";
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
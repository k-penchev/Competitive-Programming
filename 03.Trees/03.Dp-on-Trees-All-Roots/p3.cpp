#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, k;
vector<vector<int>> tree(MAXN);
int farthestNode, farthestDist;
int diameter1, diameter2;
int parent[MAXN];
int dp[MAXN];

void dfs2(int node, int par)
{
    int best1 = 0, best2 = 0;

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs2(to, node);

        int candidate = dp[to];

        if(candidate > best1)
        {
            best2 = best1;
            best1 = candidate;
        }
        else if(candidate > best2)
        {
            best2 = candidate;
        }
    }

    diameter2 = max({diameter2, best1, best1 + best2});
    dp[node] += best1;
}

void dfs1(int node, int par, int currDist)
{
    parent[node] = par;

    if(currDist > farthestDist)
    {
        farthestDist = currDist;
        farthestNode = node;
    }

    for(const int& to : tree[node])
    {
        if(to == par) continue;
        dfs1(to, node, currDist + 1);
    }
}


void find_farthest(int node, int par, int currDist)
{
    fill(parent + 1, parent + n + 1, 0);
    farthestDist = -1;
    
    dfs1(node, par, currDist);
}

void solve()
{
    cin >> n >> k;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
        dp[a] = dp[b] = 1;
    }

    find_farthest(1, 0, 0);
    int A = farthestNode;

    find_farthest(A, 0, 0);
    int B = farthestNode;

    diameter1 = farthestDist;

    if(k == 1)
    {
        cout << 2 * (n - 1) - diameter1 + 1 << "\n";
    }
    else 
    {
        int v = B;
        while(v != parent[v])
        {
            dp[v] = -1;
            v = parent[v];
        }

        dfs2(B, 0);

        cout << 2 * (n - 1) - diameter1 - diameter2 + 2 << "\n";
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
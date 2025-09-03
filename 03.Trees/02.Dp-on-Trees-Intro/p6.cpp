#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400 + 2;
const int INF = 1e9;

int n, k;
vector<int> tree[MAXN];
int id[MAXN][MAXN];
int dp[MAXN][MAXN];
int take[MAXN][MAXN][MAXN];
int siz[MAXN], parent[MAXN];
vector<int> edges;

void dfs3(int node, int par, int removedCnt)
{
    if(siz[node] == removedCnt)
    {
        edges.push_back(id[node][par]);
        return;
    }

    vector<int> children;
    
    for (int to : tree[node]) if (to != par) children.push_back(to);
    
    for (int i = (int)children.size() - 1; i >= 0; --i)
    {
        int to = children[i];
        int x = take[node][to][removedCnt];
        
        dfs3(to, node, x);
        
        removedCnt -= x;
    }
}

void dfs2(int node, int par)
{
    dp[node][0] = 0;

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs2(to, node);

        for(int i = siz[node] ; i >= 0 ; --i)
        {
            for(int j = 0 ; j <= min(i, siz[to]) ; ++j)
            {
                if(dp[node][i - j] + dp[to][j] < dp[node][i])
                {
                    dp[node][i] = dp[node][i - j] + dp[to][j];
                    take[node][to][i] = j;
                }
            }
        }
    }

    dp[node][siz[node]] = (node == 1 ? 0 : 1); 
}

void dfs1(int node, int par)
{
    siz[node] = 1;

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        parent[to] = node;

        dfs1(to, node);

        siz[node] += siz[to];
    }
}

void solve()
{
    cin >> n >> k;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);

        id[a][b] = id[b][a] = i;
    }

    parent[1] = 0;
    dfs1(1, 0);
    
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            dp[i][j] = INF;
        }
    }

    dfs2(1, 0);

    int bestCnt = dp[1][n - k], bestNode = 1;

    for (int i = 2; i <= n; ++i)
    {
        if (siz[i] >= k)
        {
            int cand = 1 + dp[i][siz[i] - k];
            
            if (cand < bestCnt)
            {     
                bestCnt = cand;
                bestNode = i;
            }
        }
    }


    if(bestNode != 1)
    {
        edges.push_back(id[bestNode][parent[bestNode]]);
    }

    dfs3(bestNode, parent[bestNode], siz[bestNode] - k);

    cout << bestCnt << "\n";

    for(int edge : edges)
    {
        cout << edge << " ";
    }

    cout << "\n";
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
}
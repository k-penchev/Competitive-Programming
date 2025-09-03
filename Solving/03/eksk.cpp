#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;

int N, A, B;
vector<vector<int>> tree(MAXN);
int parent[MAXN];

vector<int> path;
bool onPath[MAXN];

vector<int> depths;
int maxDepth[MAXN];

int prefix[MAXN], suffix[MAXN];

void dfs2(int node, int par, int currDepth)
{
    depths.push_back(currDepth);

    for(const int& to : tree[node])
    {
        if(to == par || onPath[to]) continue;

        dfs2(to, node, currDepth + 1);
    }
}

void dfs1(int node, int par)
{
    for(const int& to : tree[node])
    {
        if(to == par) continue;
        parent[to] = node;
        dfs1(to, node);
    }
}

void solve()
{
    cin >> N;

    for(int i = 1 ; i <= N - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    cin >> A >> B;

    parent[A] = -1;
    dfs1(A, -1);

    int currNode = B;
    while(currNode != -1)
    {
        onPath[currNode] = true;
        path.push_back(currNode);
        currNode = parent[currNode];
    }

    reverse(path.begin(), path.end());

    for(int p : path)
    {
        depths.clear();
        dfs2(p, -1, 0);
        maxDepth[p] = *max_element(depths.begin(), depths.end());
    }

    int m = (int)path.size() - 1;  

    prefix[0] = 0 + maxDepth[path[0]];
    for (int i = 1; i <= m; ++i) {
        prefix[i] = max(prefix[i - 1], i + maxDepth[path[i]]);
    }

    suffix[m] = 0 + maxDepth[path[m]];
    for (int i = m - 1; i >= 0; --i) {
        suffix[i] = max(suffix[i + 1], (m - i) + maxDepth[path[i]]);
    }

    for (int i = 0; i <= m-1; ++i)
    {                
        cout << prefix[i] << " " << suffix[i + 1] << "\n";
    }

    int answer = 0;
    for (int i = 0; i <= m - 1; ++i)
    {                
        answer = max(answer, min(prefix[i], suffix[i+1]));
    }

    cout << answer + 1 << "\n";
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
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int MAXM = 1e5 + 40;
const int MAXV = 50;
const int INF = 1e18;
const int MAXLOG = 20;

int n, m, q;

struct Edge
{
    int a;
    int b;
    int w;
};

//mst
Edge edges[MAXM];
int sorted[MAXM];
bool selected[MAXM];
vector<vector<pair<int, int>>> tree(MAXN);

//euler
int in[MAXN], tour[2 * MAXN], depth[MAXN], timer = 1;
int distT[MAXN];

//graph
vector<vector<pair<int, int>>> g(MAXN);
int distG[MAXV][MAXN], vCnt = 0;
priority_queue<pair<int, int>> pq;

struct Sparse
{
    int sparse[2 * MAXN][MAXLOG];
    int lg[2 * MAXN];

    void build(int arr[], int size)
    {
        lg[1] = 0;

        for(int i = 2 ; i <= size ; ++i) lg[i] = lg[i / 2] + 1;

        for(int i = 1 ; i <= size ; ++i) sparse[i][0] = arr[i];

        for(int j = 1 ; (1 << j) <= size ; ++j)
        {
            for(int i = 1 ; i + (1 << j) - 1 <= size ; ++i)
            {
                int L = sparse[i][j - 1];
                int R = sparse[i + (1 << (j - 1))][j - 1];

                sparse[i][j] = (depth[L] < depth[R] ? L : R);
            }
        }

    }

    int query(int l, int r)
    {
        if (l > r) swap(l, r);

        int k = lg[r - l + 1];

        int L = sparse[l][k];
        int R = sparse[r - (1 << k) + 1][k];

        return (depth[L] < depth[R] ? L : R);
    }
};

Sparse table;
set<int> vertecies;

struct DSU
{
    int par[MAXN], sz[MAXN];

    void set()
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x)
    {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY)
        {
            if(sz[rootX] < sz[rootY])
            {
                par[rootX] = rootY;
                sz[rootY] += sz[rootX];
            }
            else
            {
                par[rootY] = rootX;
                sz[rootX] += sz[rootY];
            }
        }
    }

    bool areConnected(int x, int y)
    {
        return (find(x) == find(y));
    }
};

DSU dsu;

void mst()
{
    dsu.set();

    iota(sorted + 1, sorted + m + 1, 1);
    sort(sorted + 1, sorted + m + 1, [&](int x, int y)
    {
        return edges[x].w < edges[y].w;
    });

    int cnt = 0;

    for(int i = 1 ; i <= m ; ++i)
    {
        auto [from, to, w] = edges[sorted[i]];
        if(cnt == n - 1) break;

        if(!dsu.areConnected(from, to))
        {
            dsu.unite(from, to);

            tree[from].push_back({to, w});
            tree[to].push_back({from, w});
            selected[sorted[i]] = true;

            cnt++;
        }
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        if(!selected[sorted[i]])
        {
            auto& [from, to, w] = edges[sorted[i]];
            vertecies.insert(from);
            vertecies.insert(to);
        }
    }
}



void euler(int node, int par, int currentDepth, int currentDist)
{
    in[node] = timer;

    tour[timer++] = node;
    depth[node] = currentDepth;
    distT[node] = currentDist;
    
    for(auto& [to, w] : tree[node])
    {
        if(to == par) continue;
        euler(to, node, currentDepth + 1, currentDist + w);
        tour[timer++] = node;
    }
}

void dijkstra(int source)
{
    ++vCnt;

    for(int i = 1 ; i <= n ; ++i)
    {
        distG[vCnt][i] = INF;
    }

    distG[vCnt][source] = 0;
    
    pq.push({0, source});

    while(pq.size())
    {
        int currNode = pq.top().second;
        int currDist = -pq.top().first;
        pq.pop();

        if(currDist > distG[vCnt][currNode]) continue;

        for(auto& [to, w] : g[currNode])
        {
            if(currDist + w < distG[vCnt][to])
            {
                distG[vCnt][to] = currDist + w;
                pq.push({-distG[vCnt][to], to});
            }
        }
    }
}

void init()
{
    mst();

    euler(1, 0, 0, 0);
    table.build(tour, 2 * n - 1);

    for(auto it = vertecies.begin() ; it != vertecies.end() ; ++it)
    {
        dijkstra(*it);
    }
}

int query(int a, int b)
{
    int ans = INF;

    int lca = table.query(in[a], in[b]);

    ans = min(ans, distT[a] + distT[b] - 2 * distT[lca]);

    for(int i = 1 ; i <= vCnt ; ++i)
    {
        ans = min(ans, distG[i][a] + distG[i][b]);
    }

    return ans;
}

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;

        g[a].push_back({b, w});
        g[b].push_back({a, w});

        edges[i] = {a, b, w};
    }

    init();

    cin >> q;

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int a, b; cin >> a >> b;
        cout << query(a, b) << "\n";
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

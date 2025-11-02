#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int MAXLOG = 20;
const int MAXT = 2 * 1e5 + 10;
const int INF = 1e18;

int n, m, q, t;
vector<pair<int, int>> tree[MAXN];

struct Event
{
    int type;
    int idx;
    int node;
    int start;
    int end;
    int w;
};

vector<Event> event;
int ans[MAXN];

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    int centroidPar[MAXN][MAXLOG];
    int centroidDist[MAXN][MAXLOG];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> centroidData[MAXN];

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

    void calcDfs(int node, int par, int currDist, int globalCentroid, int globalLevel)
    {
        centroidPar[node][globalLevel] = globalCentroid;
        centroidDist[node][globalLevel] = currDist;

        for(const auto& [child, w] : tree[node])
        {
            if(child == par || vis[child]) continue;
            calcDfs(child, node, currDist + w, globalCentroid, globalLevel);
        }
    }

    void decompose(int node, int lvl)
    {
        findSize(node, 0);
        int cntr = findCentroid(node, 0, sz[node]);

        vis[cntr] = 1;
        calcDfs(cntr, 0, 0, cntr, lvl);

        for(const auto& [child, w] : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child, lvl + 1);
        }
    }

    void build()
    {
        decompose(1, 0);
    }

    int propagate(int node, int time)
    {
        int best = INF;

        for(int i = 0 ; i < MAXLOG ; ++i)
        {
            int cntr = centroidPar[node][i];
            int dist = centroidDist[node][i];

            if(cntr == 0) break;

            while(centroidData[cntr].size() && centroidData[cntr].top().second > time)
            {
                centroidData[cntr].pop();
            }

            if(centroidData[cntr].size())
                best = min(best, 1LL * dist + 1LL * centroidData[cntr].top().first);
        }

        return best;
    }

    void seed(int node, int time, int cost)
    {
        for(int i = 0 ; i < MAXLOG ; ++i)
        {
            int cntr = centroidPar[node][i];
            int dist = centroidDist[node][i];

            if(cntr == 0) break;
            centroidData[cntr].push({cost + dist, time});
        }
    }

    void update(int node, int start, int end, int w)
    {
        int best = propagate(node, start);
        if(best == INF) return;

        int source = best + w;

        for(int i = 0 ; i < MAXLOG ; ++i)
        {
            int cntr = centroidPar[node][i];
            int dist = centroidDist[node][i];

            if(cntr == 0) break;
            centroidData[cntr].push({source + dist, end});
            
        }
    }

    int query(int node, int time)
    {
        return propagate(node, time);
    }
};

void solve()
{
    sort(event.begin(), event.end(), [&](const Event& a, const Event& b)
    {
        return a.start > b.start;
    });

    Centroid::build();
    Centroid::seed(1, t, 0);
    for(auto& [type, idx, node, start, end, w] : event)
    {
        if(type == 1) //update
        {
            Centroid::update(node, start, end, w);
        }
        else //query
        {
            ans[idx] = Centroid::query(node, start);
        }
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        cout << (ans[i] == INF ? -1 : ans[i]) << "\n";
    }
}

void read()
{
    cin >> n >> m >> q >> t;

    for(int i = 1 ; i <= n - 1; ++i)
    {
        int a, b, w; 
        cin >> a >> b >> w; ++a, ++b;
        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int node, start, end, w; 
        cin >> node >> start >> end >> w; ++node;
        event.push_back({1, i, node, start, end, w});
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int time, node; 
        cin >> time >> node; ++node;
        event.push_back({2, i, node, time, -1, -1});
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
    read();
    solve();
}
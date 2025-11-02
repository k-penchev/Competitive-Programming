#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, m;

struct Line
{
    int a, b;
};

vector<Line> line;
vector<vector<int>> region;
map<pair<int, int>, int> who;
vector<vector<int>> tree(MAXN);

namespace Centroid
{
    int sz[MAXN];
    bool vis[MAXN];
    int color[MAXN];

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

    void decompose(int node, int c)
    {
        findSize(node, -1);
        int cntr = findCentroid(node, -1, sz[node]);

        vis[cntr] = 1;
        color[cntr] = c;

        for(const int& child : tree[cntr])
        {
            if(vis[child]) continue;
            decompose(child, c + 1);
        }
    }

    void build()
    {
        decompose(0, 1);
    }
};

int leftSide(Line x)
{
    return x.b - x.a - 1;
}

int rightSide(Line x)
{
    return n - 2 - (x.b - x.a - 1);
}

int distance(Line x)
{
    return min(leftSide(x), rightSide(x));
}

void solve()
{
    
    sort(line.begin(), line.end(), [&](const Line& a, const Line& b)
    {
        return distance(a) < distance(b);
    });

    
    set<int> active;

    for(int i = 1 ; i <= n ; ++i) 
    {
        active.insert(i);
    }

    for(int i = 0 ; i < m ; ++i)
    {
        region.emplace_back();
        auto& [a, b] = line[i];

        if(leftSide(line[i]) <= rightSide(line[i]))
        {
            region.back().push_back(a);

            auto it = active.upper_bound(a);

            while(it != active.end() && (*it) < b)
            {
                region.back().push_back(*it);
                ++it;
                active.erase(prev(it));
            }

            region.back().push_back(b);
        }
        else
        {
            region.back().push_back(b);

            auto it = active.upper_bound(b);

            while(it != active.end())
            {
                region.back().push_back(*it);
                ++it;
                active.erase(prev(it));
            }

            it = active.begin();

            while(it != active.end() && (*it) < a)
            {
                region.back().push_back(*it);
                ++it;
                active.erase(prev(it));
            }

            region.back().push_back(a);
        }

        sort(region.back().begin(), region.back().end(), [&](int x, int y)
        {
            return x > y;
        });
    }

    
    region.emplace_back();
    for(int x : active)
    {
        region.back().push_back(x);
    }

    sort(region.back().begin(), region.back().end(), [&](int x, int y)
    {
        return x > y;
    });

    sort(region.begin(), region.end());

    int regionCnt = region.size();

    for(int i = 0 ; i < regionCnt ; ++i)
    {
        int sz = region[i].size();

        for(int j = 0 ; j < sz ; ++j)
        {
            int a = region[i][j], b = region[i][(j + 1) % sz];

            if(a > b) swap(a, b);

            if(who.count({a, b}))
            {
                int x = who[{a, b}];

                tree[i].push_back(x);
                tree[x].push_back(i);
            }
            else
            {
                who[{a, b}] = i;
            }
        }
    }

    Centroid::build();

    for(int i = 0 ; i < regionCnt ; ++i)
    {
        cout << Centroid::color[i] << " ";
    }

    cout << "\n";
}

void input()
{
    cin >> n >> m;

    for(int i = 0 ; i < m ; ++i)
    {
        int a, b; 
        cin >> a >> b;

        if(a > b) swap(a, b);
        line.push_back({a, b});
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
    input();
    solve();
}
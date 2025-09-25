#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int INF = 1e18;

int N;
vector<vector<int>> tree(MAXN);
int down[MAXN], up[MAXN], best1[MAXN], best2[MAXN], through[MAXN];
int answer[MAXN];

void dfs2(int node, int par)
{
    for(const int& to : tree[node])
    {
        if(to == par) continue;

        int other = (to == through[node] ? best2[node] : best1[node]);

        up[to] = 1 + max(up[node], other);

        dfs2(to, node);
    }
}

void dfs1(int node, int par)
{
    for(const int& to : tree[node])
    {
        if(to == par) continue;

        dfs1(to, node);

        int cand = 1 + down[to];

        if(cand > best1[node])
        {
            best2[node] = best1[node];
            best1[node] = cand;
            through[node] = to;
        }
        else if(cand > best2[node])
        {
            best2[node] = cand;
        }
    }

    down[node] = best1[node];
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

    dfs1(1, 0);
    dfs2(1, 0);

    int minimum = INF;

    for(int i = 1 ; i <= N ; ++i)
    {
        answer[i] = max(down[i], up[i]);
        minimum = min(minimum, answer[i]);
    }

    vector<int> cities;

    for(int i = 1 ; i <= N ; ++i)
    {
        if(answer[i] == minimum)
        {
            cities.push_back(i);
        }
    }

    cout << cities.size() << "\n";

    for(int c : cities)
    {
        cout << c << " ";
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
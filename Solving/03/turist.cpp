#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;

int N, M, T;
vector<vector<int>> tree(MAXN);
int w[MAXN], answer[MAXN];
int down[MAXN], up[MAXN], best1[MAXN], best2[MAXN], through[MAXN];

void dfs2(int node, int par)
{
    for(const int& to : tree[node])
    {
        if(to == par) continue;

        int other = (to == through[node] ? best2[node] : best1[node]);

        up[to] = w[to] + max(up[node], other);

        dfs2(to, node);
    }
}


void dfs1(int node, int par)
{
    bool isLeaf = true;

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        isLeaf = false;

        dfs1(to, node);

        int candidate = w[node] + down[to];

        if(candidate > best1[node])
        {
            best2[node] = best1[node];
            best1[node] = candidate;
            through[node] = to;
        }
        else if(candidate > best2[node])
        {
            best2[node] = candidate;
        }
    }

    if(isLeaf)
    {
        down[node] = w[node];
    }
    else
    {
        down[node] = best1[node];
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

    cin >> M;

    for(int i = 1 ; i <= M ; ++i)
    {
        int a, k; cin >> a >> k;
        w[a] = k;
    }

    dfs1(1, 0);
    dfs2(1, 0);

    for(int i = 1 ; i <= N ; ++i)
    {
        answer[i] = max(down[i], up[i]);
    }

    cin >> T;

    for(int i = 1 ; i <= T ; ++i)
    {
        int a; cin >> a;
        cout << answer[a] - w[a] << " ";
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
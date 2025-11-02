#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
int changedTo[MAXN];

int dfs(int node, int par)
{
    int total = 0;

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        total += dfs(to, node);
    }

    if(par != 0 && changedTo[node] == node)
    {
        changedTo[node] = changedTo[par];
        changedTo[par] = node;
        total += 2;
    }
    else if(par == 0 && changedTo[node] == node)
    {
        for(const int& to : tree[node])
        {
            if(to == par) continue;

            changedTo[node] = changedTo[to];
            changedTo[to] = node;
            total += 2;
            
            break;
        }
    }

    return total;
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        changedTo[i] = i;
    }

    int answer = dfs(1, 0);

    cout << answer << "\n";

    for(int i = 1 ; i <= n ; ++i)
    {
        cout << changedTo[i] << " ";
    }

    cout << "\n";
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
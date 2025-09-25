#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2e5 + 10;

int N;
vector<vector<int>> tree(MAXN);
vector<int> tour;

void euler(int node, int par)
{
    tour.push_back(node);

    for(const int& to : tree[node])
    {
        if(to == par) continue;

        euler(to, node);
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

    for(auto& t : tree)
    {
        sort(t.begin(), t.end());
    }

    euler(1, 0);

    for(int t : tour)
    {
        cout << t << " ";
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
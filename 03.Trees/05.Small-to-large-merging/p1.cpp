#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
vector<vector<int>> tree(MAXN);
map<int, int> cnt[MAXN];
map<int, long long> sum[MAXN];
long long ans[MAXN];

void dfs(int node, int par)
{
    for(const int& child : tree[node])
    {
        if(child == par) continue;

        dfs(child, node);

        if(cnt[node].size() < cnt[child].size())
        {
            swap(cnt[node], cnt[child]);
            swap(sum[node], sum[child]);
        }

        for(auto [color, cntC] : cnt[child])
        {
            if(cnt[node].count(color))
            {
                sum[node][cnt[node][color]] -= color; 
            }

            cnt[node][color] += cntC;
            sum[node][cnt[node][color]] += color; 
        }

    }

    ans[node] = sum[node].rbegin()->second;
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        int x; cin >> x;
        cnt[i][x] += 1;
        sum[i][1] += x;
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0);

    for(int i = 1 ; i <= n ; ++i) cout << ans[i] << " ";
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
    
    return 0;
}
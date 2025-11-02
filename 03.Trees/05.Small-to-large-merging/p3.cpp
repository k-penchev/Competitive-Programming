#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long

using namespace std;
using namespace __gnu_pbds;

using ordered_set = tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const int MAXN = 4 * 1e5 + 10;

int n;
map<int, ordered_set> mp;
int invCnt[MAXN];
int cur_id;

void dfs(int node)
{
    int val; cin >> val;

    if(val == 0)
    {
        int left = ++cur_id;
        dfs(left);
        
        int right = ++cur_id;
        dfs(right);

        if(mp[left].size() < mp[right].size())
        {
            swap(left, right);
            
        }

        int keep = 0, change = 0;
        
        for(int num : mp[right])
        {
            keep += mp[left].size() - mp[left].order_of_key(num);
            change += mp[left].order_of_key(num);
        }

        invCnt[node] = invCnt[left] + invCnt[right] + min(keep, change);

        for(int num : mp[right]) mp[left].insert(num);

        mp[node].swap(mp[left]);
        mp.erase(left); mp.erase(right);
    }
    else if(val > 0)
    {
        mp[node].insert(val);
    }
}

void solve()
{
    cin >> n;

    cur_id = 1;
    dfs(1);

    cout << invCnt[1] << "\n";
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
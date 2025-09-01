#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int MAXR = 25000 + 10;
const int SQRT = 450;

int n, r, q;
vector<vector<int>> tree(MAXN);
int region[MAXN], cnt[MAXR];
vector<vector<int>> byRegion;

bool isHeavy[MAXR];
vector<unordered_map<int, int>> calcHeavy;
vector<vector<int>> calcLight;

int in[MAXN], out[MAXN], timer = 0;

int cntCurrentHeavyRegion = 0; 

void dfsHeavy(int node, int par, int currentHeavyRegion)
{
    if(region[node] == currentHeavyRegion)
    {
        calcHeavy[currentHeavyRegion][currentHeavyRegion] += cntCurrentHeavyRegion;
        cntCurrentHeavyRegion++;
    }
    else
    {
        calcHeavy[currentHeavyRegion][region[node]] += cntCurrentHeavyRegion;
    }

    for(int& to : tree[node])
    {
        if(to == par) continue;
        dfsHeavy(to, node, currentHeavyRegion);
    }

    if(region[node] == currentHeavyRegion)
    {
        cntCurrentHeavyRegion--;
    }
}

void dfsLight(int node, int par)
{
    in[node] = ++timer;

    if(!isHeavy[region[node]])
    {
        calcLight[region[node]].push_back(node);
    }
    
    byRegion[region[node]].push_back(in[node]);

    for(int& to : tree[node])
    {
        if(to == par) continue;
        dfsLight(to, node);
    }

    out[node] = timer;
}

int binary(vector<int>& v, int k)
{
    int l = -1, r = v.size();

    while(r > l + 1)
    {
        int m = (l + r) / 2;

        if(v[m] >= k) r = m;
        else l = m;
    }

    return r;
}

int query(int x, int y)
{
    if(isHeavy[x])
    {
        return calcHeavy[x][y];
    }

    int answer = 0;

    for(int& child : calcLight[x])
    {
        int low = binary(byRegion[y], in[child]);
        int high = binary(byRegion[y], out[child] + 1);

        answer += high - low;
    }

    return answer;
}

void solve()
{
    cin >> n >> r >> q;

    cin >> region[1];

    cnt[region[1]]++;

    for(int i = 2 ; i <= n ; ++i)
    {
        int parent; cin >> parent >> region[i]; 

        cnt[region[i]]++;
        tree[parent].push_back(i);
        tree[i].push_back(parent);
    }

    byRegion.assign(r + 1, {});
    calcHeavy.assign(r + 1, {});  
    calcLight.resize(r + 1);

    for(int i = 1 ; i <= r ; ++i)
    {
        if(cnt[i] >= SQRT) 
        {
            isHeavy[i] = true;
            cntCurrentHeavyRegion = 0;

            dfsHeavy(1, 0, i);
        }
        else isHeavy[i] = false;
    }

    dfsLight(1, 0);

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int r1, r2; cin >> r1 >> r2;
        cout << query(r1, r2) << "\n"; 
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
}
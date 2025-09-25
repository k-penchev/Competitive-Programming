#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 5e4 + 10;

int n;
int a[MAXN], b[MAXN], id[MAXN];

struct Fenwick
{
    
    int bit[MAXN];

    void reset()
    {
        for(int i = 0 ; i <= n ; i++)
        {
            bit[i] = 0;
        }
    }

    void update(int idx, int val)
    {
        while(idx <= n)
        {
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int query(int idx)
    {
        int sum = 0;

        while(idx >= 1)
        {
            sum += bit[idx];
            idx -= idx & (-idx);
        }

        return sum;
    }
};

Fenwick tree;
int answer;

void solve(){
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        id[a[i]] = i;
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> b[i];
        b[i] = id[b[i]];
    }

    tree.reset();

    for(int i = n ; i >= 1 ; --i)
    {
        answer += tree.query(b[i] - 1);
        tree.update(b[i], +1);
    }

    cout << answer << "\n";
}


void fastIO(){
    ios :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main(){
    fastIO();
    solve();
}
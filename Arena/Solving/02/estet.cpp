#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
vector<int> v;
int dpLeft[MAXN], dpRight[MAXN];

struct Fenwick
{
    int bit[MAXN];

    void reset()
    {
        memset(bit, 0, sizeof(bit));
    }

    void update(int idx, int val)
    {
        for(; idx < MAXN ; idx += (idx & (-idx)))
        {
            bit[idx] = max(bit[idx], val);
        }
    }

    int query(int idx)
    {
        int res = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            res = max(res, bit[idx]);
        }

        return res;
    }
};

Fenwick tree;
int answer = 0;

void solve()
{
    answer = 0;                          // reset the answer for a fresh run

    for(int i = 0 ; i < n ; ++i)
    {
        dpLeft[i] = 1;
        dpRight[i] = 1;
    }

    tree.reset();

    for(int i = 0 ; i < n ; ++i)
    {
        int idx = min(v[i] + 1, MAXN - 1);     
        int maxVal = tree.query(idx - 1);    

        dpLeft[i] = 1 + maxVal;

        tree.update(idx, dpLeft[i]);           

        answer = max(answer, dpLeft[i]);
    }

    tree.reset();
    
    for(int i = n - 1 ; i >= 0 ; --i)
    {
        int idx = min(v[i] + 1, MAXN - 1);     
        int maxVal = tree.query(idx - 1);     

        dpRight[i] = 1 + maxVal;

        tree.update(idx, dpRight[i]);         

        answer = max(answer, dpRight[i]);
    }

    for(int i = 0 ; i < n ; ++i)
    {
        answer = max(answer, (dpLeft[i] + dpRight[i] - 1));
    }

    cout << answer << "\n";
}

void input()
{
    cin >> n;

    v.resize(n);

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> v[i];
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

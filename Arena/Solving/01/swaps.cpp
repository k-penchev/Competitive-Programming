#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
int arr[2 * MAXN];
int sorted[MAXN];
int byPairs[2 * MAXN];

struct Fenwick
{
    int bit[2* MAXN];

    void reset()
    {
        for(int i = 1 ; i <= 2 * n ; ++i)
        {
            bit[i] = 0;
        }
    }

    void update(int idx, int val)
    {
        for(; idx <= 2 * n ; idx += (idx & (-idx)))
        {
            bit[idx] += val;
        }
    }

    long long query(int idx)
    {
        long long sum = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            sum += bit[idx];
        }
        
        return sum;
    }
};

Fenwick tree;

bool compare(int x, int y)
{
    return max(arr[2 * x - 1], arr[2 * x]) < max(arr[2 * y - 1], arr[2 * y]);
};

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= 2 * n ; ++i)
    {
        cin >> arr[i];
    }

    iota(sorted + 1, sorted + n + 1, 1);
    sort(sorted + 1, sorted + n + 1, compare);


    /*
    for(int i = 1 ; i <= n ; ++i)
    {
        cout << sorted[i] << " ";
    }

    cout << "\n";

    for(int i = 1 ; i <= n ; ++i)
    {
        cout << 2 * sorted[i] - 1 << " " << 2 * sorted[i] << " ";
    }

    cout << "\n";

    
    for(int i = 1 ; i <= n ; ++i)
    {
        cout << arr[2 * sorted[i] - 1] << " " << arr[2 * sorted[i]] << " ";
    }

    cout << "\n";
    */

    for(int i = 1 ; i <= n ; ++i)
    {
        byPairs[2 * i - 1] = arr[2 * sorted[i] - 1];
        byPairs[2 * i] = arr[2 * sorted[i]];
    }

    long long ans = 0;
    tree.reset();

    for(int i = 2 * n ; i >= 1 ; --i)
    {
        ans += tree.query(byPairs[i] - 1);
        tree.update(byPairs[i], +1);
    }

    cout << ans << "\n";
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
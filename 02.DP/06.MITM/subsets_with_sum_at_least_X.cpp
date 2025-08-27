#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 36;

int n, x;
int a[MAXN];
vector<int> leftPart, rightPart;

int binary(vector<int>& vals, int num)
{
    int l = -1, r = vals.size();

    while(r > l + 1)
    {
        int m = (l + r) / 2;

        if(vals[m] >= num) r = m;
        else l = m;
    }

    return r;
}

void calc(int l, int r, vector<int>& v)
{
    int len = r - l + 1;

    for(int mask = 0 ; mask < (1 << len) ; ++mask)
    {
        int s = 0;

        for(int i = 0 ; i < len ; ++i)
        {
            if(mask & (1 << i))
            {
                s += a[l + i];
            }
        }

        v.push_back(s);
    }
}

void solve()
{
    cin >> n >> x;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> a[i];
    }

    // [0 , n / 2 - 1] , [n / 2 , n - 1]

    int middle = n / 2;

    calc(0, middle - 1, leftPart);
    calc(middle, n - 1, rightPart);

    sort(leftPart.begin(), leftPart.end());
    sort(rightPart.begin(), rightPart.end());

    int cnt = 0;

    for(int s : leftPart)
    {
        int low = binary(rightPart, x - s);
        cnt += rightPart.size() - low;
    }

    cout << cnt << "\n";
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
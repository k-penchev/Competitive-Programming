#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 35;

int n, m;
int a[MAXN];
vector<int> lPart, rPart;

int binary(vector<int>& v, int num)
{
    int l = -1, r = v.size();

    while(r > l + 1)
    {
        int mid = (l + r) / 2;

        if(v[mid] > num) r = mid;
        else l = mid;
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
                s = (s + a[l + i]) % m;
            }
        }

        v.push_back(s);
    }
}

void solve()
{
    cin >> n >> m;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> a[i];
    }

    int middle = n / 2;

    calc(0, middle - 1, lPart);
    calc(middle, n - 1, rPart);

    sort(lPart.begin(), lPart.end());
    sort(rPart.begin(), rPart.end());

    int best = 0;

    for(int s : lPart)
    {
        int idx = binary(rPart, m - 1 - s);
        
        if(idx == 0) continue;

        --idx;
        best = max(best, s + rPart[idx]);
    }

    cout << best << "\n";
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
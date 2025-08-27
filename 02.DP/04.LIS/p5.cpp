#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 2e5 + 10;
const int INF = 1e18;

int N, M, P;
int a[MAXN];
vector<int> v;
int dp[MAXN];

int upper_binary(int x)
{
    int l = -1, r = P;

    while(r > l + 1)
    {
        int m = (l + r) / 2;

        if(dp[m] > x)
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }

    return r;
}

void solve()
{
    cin >> N >> M;

    for(int i = 1 ; i <= N ; ++i)
    {
        cin >> a[i];
    }

    for(int i = 1 ; i <= N ; ++i)
    {
        if(M * i >= a[i])
        {
            v.push_back(M * i - a[i]);
        }
    }

    P = v.size();

    for(int i = 1 ; i <= P ; ++i)
    {
        dp[i] = INF;
    }

    dp[0] = -INF;

    for(int val : v)
    {
        int idx = upper_binary(val);

        dp[idx] = val;
    }

    int answer = 0;

    for(int i = 1 ; i <= P ; ++i)
    {
        if(dp[i] < INF)
        {
            answer = i;
        }
    }

    cout << N - answer << "\n";
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
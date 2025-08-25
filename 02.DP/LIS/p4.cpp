#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 1e5 + 10;
const int INF = 1e18;

int N, T;
pair<int, int> toCompress[MAXN];
int compressed[MAXN];
int dp[MAXN];

int upper_binary_search(int x)
{
    int lPtr = -1, rPtr = N;

    while(rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(dp[mid] > x)
        {
            rPtr = mid;
        }
        else
        {
            lPtr = mid;
        }
    }

    return rPtr;
}

void solve()
{
    
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);
    

    cin >> N >> T;

    int pos, speed;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> pos >> speed;
        toCompress[i] = {pos + T * speed, i};
    }

    sort(toCompress, toCompress + N);

    int cnt = 0;

    for(int i = 0 ; i < N ; ++i)
    {
        compressed[toCompress[i].second] = cnt;
        if(i + 1 < N)
            cnt += (toCompress[i].first != toCompress[i + 1].first);
    }

    for(int i = 0 ; i <= N ; ++i)
    {
        dp[i] = INF;
    }

    dp[0] = -INF;

    for(int i = 0 ; i < N ; ++i)
    {
        int x = -compressed[i];

        int l = upper_binary_search(x);

        dp[l] = x;
    }

    int answer = 0;

    for(int i = 0 ; i <= N ; ++i)
    {
        if(dp[i] < INF)
        {
            answer = i;
        }
    }

    cout << answer << "\n";
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
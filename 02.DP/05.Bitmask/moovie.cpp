#include <bits/stdc++.h>

using namespace std;

typedef long long llong;

const int MAXN = 20;
const llong INF = 1e18;

int N, L;

struct Movie
{
    int duration;
    int showtimeCnt;
    vector<int> showing;
};

Movie movie[MAXN];
int dp[(1 << MAXN)]; // maxL

int binary(vector<int>& v, int val)
{
    int l = -1, r = v.size();

    while(r > l + 1)
    {
        int m = (l + r) / 2;

        if(v[m] > val) r = m;
        else l = m;
    }

    return r;
}

void solve()
{
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);

    cin >> N >> L;
   
    for(int i = 0 ; i < N ; ++i)
    {
        cin >> movie[i].duration >> movie[i].showtimeCnt;

        for(int j = 0 ; j < movie[i].showtimeCnt ; ++j)
        {
            int x; cin >> x;
            movie[i].showing.push_back(x);
        }
    }

    for(int mask = 0 ; mask < (1 << N) ; ++mask)
    {
        dp[mask] = -1;
    }

    dp[0] = 0;

    for(int mask = 0 ; mask < (1 << N) ; ++mask)
    {
        if (dp[mask] < 0) continue;

        for(int j = 0 ; j < N ; ++j)
        {
            if((mask & (1 << j))) continue;

            int idx = binary(movie[j].showing, dp[mask]);

            if (idx == 0) continue;

            int best = movie[j].showing[idx - 1] + movie[j].duration;

            if(best >= dp[mask])
            {
                dp[mask | (1 << j)] = max(dp[mask | (1 << j)], best);
            }
         }
    }

    llong answer = INF;

    for(int mask = 1 ; mask < (1 << N) ; ++mask)
    {
        if(dp[mask] >= L)
        {
            answer = min(answer, 1LL * (__builtin_popcount(mask)));
        }
   }

    if(answer == INF)
    {
        cout << "-1" << "\n";
    }
    else
    {
        cout << answer << "\n";
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
    solve();
}
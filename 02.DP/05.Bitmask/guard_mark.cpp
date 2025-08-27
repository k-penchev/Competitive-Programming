#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;
const int INF = 1e9 + 10;

int N, H;

struct Cow
{
    int h;
    int w;
    int s;
};

Cow cow[MAXN];
pair<int, int> dp[(1 << MAXN)]; // current H, max safety

void solve()
{
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);

    cin >> N >> H;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> cow[i].h >> cow[i].w >> cow[i].s;
    }

    dp[0] = {0, INF};

    for(int mask = 1 ; mask < (1 << N) ; ++mask)
    {
        dp[mask] = {0, -1};

        for(int j = 0 ; j < N ; ++j)
        {
            if(mask & (1 << j))
            {
                auto prev = dp[mask ^ (1 << j)];
                
                dp[mask].first += cow[j].h;

                dp[mask].second = max(dp[mask].second, min(prev.second - cow[j].w, cow[j].s));
            }
        }
    }

    int max_safety = -1;
    
    for(int mask = 1 ; mask < (1 << N) ; ++mask)
    {
        if(dp[mask].first >= H)
        {
            max_safety = max(max_safety, dp[mask].second);
        }
    }

    if(max_safety < 0)
    {
        cout << "Mark is too tall" << "\n";
    }
    else
    {
        cout << max_safety << "\n";
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
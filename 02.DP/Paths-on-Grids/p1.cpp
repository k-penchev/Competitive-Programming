#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

int H, G;

struct Cow
{
    int x, y;
};


int dist(Cow& p1, Cow& p2)
{
    int f = abs(p1.x - p2.x);
    int s = abs(p1.y - p2.y);

    return f * f + s * s;
}

void solve()
{
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);

    cin >> H >> G;

    vector<Cow> h(H + 1), g(G + 1);

    int x, y;

    for(int i = 1 ; i <= H ; ++i)
    {
        cin >> x >> y;
        h[i] = {x, y};
    }

    for(int i = 1 ; i <= G ; ++i)
    {
        cin >> x >> y;
        g[i] = {x, y};
    }

    int dp[1001][1001][2];


    for(int i = 0 ; i <= 1000; ++i)
    {
        for(int j = 0 ; j <= 1000 ; ++j)
        {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }


    dp[1][0][0] = 0;

    dp[1][1][1] = dist(h[1], g[1]);

    for(int i = 0 ; i < H + 1 ; ++i)
    {
        for(int j = 0 ; j < G + 1 ; ++j)
        {
            if(i == 1 && j == 0 || i == 1 && j == 1)
            {
                continue;
            }

            if(i > 0)
            {
                dp[i][j][0] = min(dp[i - 1][j][0] + dist(h[i - 1], h[i]), dp[i - 1][j][1] + dist(g[j], h[i]));
            }

            if(j > 0)
            {
                dp[i][j][1] = min(dp[i][j - 1][1] + dist(g[j - 1], g[j]), dp[i][j - 1][0] + dist(g[j], h[i])); 
            }
        }
    }

    cout << dp[H][G][0] << "\n";
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
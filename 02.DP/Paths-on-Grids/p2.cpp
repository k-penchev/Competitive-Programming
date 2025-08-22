#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000 + 5;
const int INF = 2e9 + 5;

int N, M;

struct Point
{
    int x;
    int y;
};

vector<Point> farmer, cow;
string farmer_dir, cow_dir;
int dp[MAXN][MAXN];

void precompute()
{
    
    for(int i = 1 ; i <= farmer_dir.size(); ++i)
    {
        char dir = farmer_dir[i - 1];

        if(dir == 'N') 
        {
            farmer[i] = {farmer[i - 1].x, farmer[i - 1].y + 1};
        }
        else if(dir == 'E')
        {
            farmer[i] = {farmer[i - 1].x + 1, farmer[i - 1].y};
        }
        else if(dir == 'S') 
        {
            farmer[i] = {farmer[i - 1].x, farmer[i - 1].y - 1};
        }
        else 
        {
            farmer[i] = {farmer[i - 1].x - 1, farmer[i - 1].y};
        }

    }


    for(int i = 1 ; i <= cow_dir.size(); ++i)
    {
        char dir = cow_dir[i - 1];

        if(dir == 'N') 
        {
            cow[i] = {cow[i - 1].x, cow[i - 1].y + 1};
        }
        else if(dir == 'E') 
        {
            cow[i] = {cow[i - 1].x + 1, cow[i - 1].y};
        }
        else if(dir == 'S') 
        {
            cow[i] = {cow[i - 1].x, cow[i - 1].y - 1};
        }
        else 
        {
            cow[i] = {cow[i - 1].x - 1, cow[i - 1].y};
        }

    }

}

int dist(Point& p1, Point& p2)
{
    int f = abs(p1.x - p2.x);
    int s = abs(p1.y - p2.y);

    return f * f + s * s;
}

void solve()
{
    precompute();

    for (int i = 0; i <= N; ++i)
    {
        for (int j = 0; j <= M; ++j)
        {
            dp[i][j] = INF;
        }
    }
        
    dp[0][0] = 0;

    // Base: only FJ moves; Bessie stays
    for (int i = 1; i <= N; ++i)
    {
        
        dp[i][0] = dp[i - 1][0] + dist(farmer[i], cow[0]);
    }

    // Base: only Bessie moves; FJ stays
    for (int j = 1; j <= M; ++j)
    {
        
        dp[0][j] = dp[0][j - 1] + dist(farmer[0], cow[j]);
    }

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= M; ++j)
        {
            int best = min({dp[i - 1][j - 1],  // both advance
                           dp[i - 1][j],    // only FJ advances
                           dp[i][j - 1]});  // only Bessie advances
            dp[i][j] = best + dist(farmer[i], cow[j]);
        }
    }

    cout << dp[N][M] << "\n";
}

void input()
{
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    cin >> N >> M;

    farmer.resize(N + 1);
    cow.resize(M + 1);

    cin >> farmer[0].x >> farmer[0].y;
    cin >> cow[0].x >> cow[0].y;

    cin >> farmer_dir >> cow_dir;
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
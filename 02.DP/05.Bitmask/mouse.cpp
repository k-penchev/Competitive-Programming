#include <bits/stdc++.h>

using namespace std;

const int MAXN = 15;
const int INF = 1e9;

int N;

struct Mouse
{
    int x, y;
    int t;
};

Mouse mouse[MAXN];
float speed[MAXN]; // speed when heading to the i-th mouse
float slowFactor;
float dp[(1 << MAXN)][MAXN]; // min time to visit all in the S and finish at J
float velocity = 0;

float distance(const Mouse& m1, const Mouse& m2)
{
    float x_axis = abs(m1.x - m2.x);
    float y_axis = abs(m1.y - m2.y);

    return sqrt(x_axis * x_axis + y_axis * y_axis);
}

bool check(float v)
{
    speed[0] = v;

    for(int i = 1 ; i < N ; ++i)
    {
        speed[i] = speed[i - 1] * slowFactor;
    }

    for(int i = 0 ; i < (1 << N) ; ++i)
    {
        for(int j = 0 ; j < N ; ++j)
        {
            dp[i][j] = INF;
        }
    }

    for(int i = 0 ; i < N ; ++i)
    {
        float currT = distance({0, 0, 0}, mouse[i]) / v;

        if(currT <= mouse[i].t)
        {
            dp[(1 << i)][i] = currT;
        }
    }

    for(int mask = 1 ; mask < (1 << N) ; ++mask)
    {
        for(int i = 0 ; i < N ; ++i)
        {
            if(mask & (1 << i))
            {
                int prev = mask ^ (1 << i);

                for(int j = 0 ; j < N ; ++j)
                {
                    if(prev & (1 << j))
                    {
                        float currV = speed[__builtin_popcount(prev)];
                        float time = dp[prev][j] + distance(mouse[i], mouse[j]) / currV;

                        if(dp[prev][j] != INF && time <= mouse[i].t)
                        {
                            dp[mask][i] = min(dp[mask][i], time);
                        }
                    }
                }
            }
        }
    }

    for(int i = 0 ; i < N ; ++i)
    {
        if(dp[(1 << N) - 1][i] != INF)
        {
            return true;
        }
    }

    return false;
}

void solve()
{
    float l = 0, r = INF;

    while(r > l + 0.001)
    {
        float m = l + (r - l) / 2;

        if(check(m))
        {
            r = velocity = m;
        }
        else
        {
            l = m;
        }
    }

    cout << velocity << "\n";
}

void input()
{
    cin >> N;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> mouse[i].x >> mouse[i].y >> mouse[i].t;
    }

    cin >> slowFactor;
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
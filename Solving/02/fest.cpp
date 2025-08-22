#include <bits/stdc++.h>

using namespace std;

int T;
int f[2];

void solve()
{
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    cin >> T >> f[0] >> f[1];

    vector<bool> dpBeforeWater(T + 1, false);
    vector<bool> dpAfterWater(T + 1, false);

    dpBeforeWater[0] = dpAfterWater[0] = true;

    //compute before
    for(int i = 0 ; i < 2 ; ++i)
    {
        for(int s = 0 ; s < T ; ++s)
        {
            if(dpBeforeWater[s] && s + f[i] <= T)
            {
                dpBeforeWater[s + f[i]] = true;
            }
        }
    }

    //propagate
    for(int i = 0 ; i <= T ; ++i)
    {
        if(dpBeforeWater[i])
        {
            dpAfterWater[i / 2] = true;
        }
    }

    //compute after
    for(int i = 0 ; i < 2 ; ++i)
    {
        for(int s = 0 ; s < T ; ++s)
        {
            if(dpAfterWater[s] && s + f[i] <= T)
            {
                dpAfterWater[s + f[i]] = true;
            }
        }
    }

    //find best answer
    int best_result = 0;

    for(int i = 0 ; i <= T ; ++i)
    {
        if(dpBeforeWater[i])
        {
            best_result = max(best_result, i);
        }

        if(dpAfterWater[i])
        {
            best_result = max(best_result, i);
        }
    }

    cout << best_result << "\n";
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
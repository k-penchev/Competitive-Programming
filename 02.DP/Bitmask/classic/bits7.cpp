//Dynamic programming
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

int N, X;
pair<int, int> best[(1 << MAXN)];
int w[MAXN];

void solve()
{
    cin >> N >> X;

    for(int person = 0 ; person < N ; ++person)
    {
        cin >> w[person];
    }

    best[0] = {1, 0};

    for(int i = 1 ; i < (1 << N) ; ++i)
    {
        best[i] = {N + 1, 0};
    }

    for(int group = 1 ; group < (1 << N) ; ++group)
    {
        for(int person = 0 ; person < N ; ++person)
        {
            if(group & (1 << person))
            {
                auto option = best[group ^ (1 << person)];

                if(option.second + w[person] <= X)
                {
                    // add current person to existing ride
                    option.second += w[person];
                }
                else
                {
                    // reserve a new ride for the current person
                    option.first++;
                    option.second = w[person];
                }

                best[group] = min(best[group], option);
            }
        }
    }

    int FULL = (1 << N) - 1;

    cout << best[FULL].first << " " << best[FULL].second << "\n";
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
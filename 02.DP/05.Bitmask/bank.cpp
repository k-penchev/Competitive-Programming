#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;
const int MAXM = 20;

int N, M;
int salary[MAXN];
int banknote[MAXM];
pair<int, int> dp[(1 << MAXM)]; // people covered, sum of leftover banknotes

void solve()
{
    cin >> N >> M;

    for(int i = 0 ; i < N ; ++i)
    {
        cin >> salary[i];
    }

    for(int i = 0 ; i < M ; ++i)
    {
        cin >> banknote[i];
    }

    for(int mask = 0 ; mask < (1 << M) ; ++mask)
    {
        dp[mask] = {-1, -1};
    }

    dp[0] = {0, 0};

    for(int mask = 0 ; mask < (1 << M) ; ++mask)
    {
        for(int i = 0 ; i < M ; ++i)
        {
            if(mask & (1 << i))
            {
                auto prev = dp[mask ^ (1 << i)];

                if(prev.first == -1) continue;

                int nextPerson = prev.first;
                int leftSum = prev.second;

                int nextBanknote = banknote[i];

                int newSum = leftSum + nextBanknote;

                if(newSum < salary[nextPerson])
                {
                    dp[mask] = {nextPerson, newSum};
                }
                else if(newSum == salary[nextPerson])
                {  
                    dp[mask] = {nextPerson + 1, 0}; 
                }
            }
        }

        if(dp[mask].first == N)
        {
            cout << "YES" << "\n";
            return;
        }
    }

    cout << "NO" << "\n";
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
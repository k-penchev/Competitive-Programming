#include <bits/stdc++.h>

using namespace std;

string st1, st2;

void solve()
{
    cin >> st1 >> st2;

    if(st2.size() > st2.size()) swap(st1, st2);

    int n = st1.size();
    int m = st2.size();

    vector<int> prev(m + 1, 0), curr(m + 1);

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= m ; ++j)
        {
            if(st1[i - 1] == st2[j - 1])
            {
                curr[j] = prev[j - 1] + 1;
            }
            else
            {
                curr[j] = max(prev[j], curr[j - 1]);
            }


        }

        prev = curr;
    }

    cout << prev[m] << "\n";
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
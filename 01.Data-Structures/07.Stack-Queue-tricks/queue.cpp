#include <bits/stdc++.h>

using namespace std;

deque<int> dq;

void solve()
{
    vector<int> v = {3, 2, 4, 1, 10, 16, 4, 2, 19};
    
    for(int i = 0 ; i < v.size() ; ++i)
    {
        if(dq.empty())
        {
            dq.push_back(v[i]);
        }
        else
        {
            while(!dq.empty() && dq.back() > v[i])
            {
                dq.pop_back();
            }

            dq.push_back(v[i]);
        }
    }

    while(dq.size())
    {
        cout << dq.back() << endl;
        dq.pop_back();
    }
}

void fastIO()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
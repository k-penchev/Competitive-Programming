#include <bits/stdc++.h>

using namespace std;

stack<pair<int, int>> st;


void solve()
{
    vector<int> v = {3, 2, 4, 1, 10, 16, 4, 2, 19, 0};
    
    for(int i = 0; i < v.size(); ++i)
    {
        if(st.empty())
        {
            st.push({v[i], v[i]});
        }
        else
        {
            int new_min = min(v[i], st.top().second);
            st.push({v[i], new_min});
        }
    }

    while(st.size())
    {
        auto [element, current_min] = st.top();

        cout << element << " " << current_min << endl;

        st.pop();
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
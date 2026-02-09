/*

    Problem: Find the smaller/greater to the left/right of each element in array.

*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

const int MAXN = 100000 + 10;
const int INF = 1e9 + 10;

int n;
int a[MAXN];
std::stack<int> st;
int prev[MAXN]; // prev[i] -> smaller to the left
int next[MAXN]; // next[i] -> smaller to the right

void solve()
{
    st.push(0);
    
    for(int i = 1 ; i <= n ; ++i)
    {
        while(!st.empty() && a[st.top()] >= a[i]) st.pop();
        prev[i] = st.top();
        st.push(i);
    }

    while(st.size()) st.pop();
    st.push(n + 1);

    for(int i = n ; i >= 1 ; --i)
    {
        while(!st.empty() && a[st.top()] >= a[i]) st.pop();
        next[i] = st.top();
        st.push(i);
    }
}

void input()
{
    std::cin >> n;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }
}

void output()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << prev[i] << " ";
    }

    std::cout << "\n";

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << next[i] << " ";
    }

    std::cout << "\n";
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    input();
    solve();
    output();
    return 0;
}
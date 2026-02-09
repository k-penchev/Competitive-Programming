#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

const int MAXN = 100000 + 10;
const int INF = 1e9 + 10;

int n;
int a[MAXN];
int left[MAXN];
int right[MAXN];
int size[MAXN];
std::stack<int> st;
int root;

void dfs(int node)
{
    size[node] = 1;

    if(left[node] != 0)
    {
        dfs(left[node]);
        size[node] += size[left[node]];
    }

    if(right[node] != 0)
    {
        dfs(right[node]);
        size[node] += size[right[node]];
    }
}

void build()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        int last = -1;
        while(st.size() && a[st.top()] > a[i])
        {
            last = st.top();
            st.pop();
        }

        if(last != -1)
        {
            left[i] = last;
        }

        if(st.size())
        {
            right[st.top()] = i;
        }
        else
        {
            root = i;
        }

        st.push(i);
    }
}

void solve()
{
    build();
    dfs(root);

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << left[i] << " ";
    }
    
    std::cout << "\n";

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << right[i] << " ";
    }
    
    std::cout << "\n";

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << size[i] << " ";
    }
    
    std::cout << "\n";
}

void input()
{
    std::cin >> n;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }
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
    
    return 0;
}
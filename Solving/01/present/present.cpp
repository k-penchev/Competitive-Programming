#include <bits/stdc++.h>

using namespace std;

const int MAXN = 350000 + 10;
const int LOG = 17;

int n;
vector<int> v;

/*
struct Fenwick
{
    
    int bit[MAXN];

    void set()
    {
        for(int i = 0 ; i <= n ; i++)
        {
            bit[i] = 0;
        }
    }

    void update(int idx, int val)
    {
        while(idx <= n)
        {
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int query(int idx)
    {
        int sum = 0;

        while(idx >= 1)
        {
            sum += bit[idx];
            idx -= idx & (-idx);
        }

        return sum;
    }
};


Fenwick fen;
*/

int question (int x, int k);

/*int binary(int l, int r)
{
    int lPtr = l - 1, rPtr = r + 1;

    while (rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(question())
        {

        }
    }
    
}
*/

std::vector <int> solve (int N)
{
    n = N;

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= i ; ++j)
        {
            int number = question(i, j);

            if(find(v.begin(), v.end(), number) != v.end())
            {
                continue;
            }
            else
            {
                v.push_back(number);
                break;
            }
        }
    }

    return v;
}




/*
void solve()
{
    
}



void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    
    return 0;
}
*/
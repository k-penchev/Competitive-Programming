#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXS = 1e7 + 5;

struct Fenwick
{
    
    int bit[MAXS];

    void reset()
    {
        for(int i = 0 ; i <= MAXS ; i++)
        {
            bit[i] = 0;
        }
    }

    void update(int idx, int val)
    {
        while(idx <= MAXS)
        {
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int query(int idx)
    {
        int sum = 0;

        while(idx > 0)
        {
            sum += bit[idx];
            idx -= idx & (-idx);
        }

        return sum;
    }
};


Fenwick cnt, sum;
bool isPrime[MAXS];

void precompute()
{
    memset(isPrime, 1, sizeof(isPrime));

    isPrime[1] = false;

    for(int i = 2 ; i * i <= MAXS ; ++i)
    {
        if(isPrime[i])
        {
            for(int j = i * 2 ; j <= MAXS ; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
}

void solve()
{
    cnt.reset();
    sum.reset();

    precompute();

    char type;
    int x, y;

    while(cin >> type)
    {

        if(type == 'a')
        {
            cin >> x;
            
            if(isPrime[x])
            {
                cnt.update(x, +1);
                sum.update(x, +x);
            }
        }
        else if(type == 'c')
        {
            cin >> x >> y;

            int c = cnt.query(y) - cnt.query(x - 1);
            int s = sum.query(y) - sum.query(x - 1);

            cout << c << " " << s << "\n";
        }
        else
        {
            cin >> x;
            
            int c = cnt.query(x) - cnt.query(x - 1);

            if(isPrime[x])
            {
                if(c)
                {
                    cnt.update(x, -1);
                    sum.update(x, -x);
                }
            }
            
        }
    }
}  

void fastIO()
{
    ios :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 350000 + 10;
const int MAX_LOG = 19;

int n;
vector<int> v;

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

    int find_kth(int val)
    {
        int pos = 0;
        int sum = 0;

        for(int lg = MAX_LOG; lg >= 0; --lg)
        {
            int next = 1 << lg;

            if(pos + next <= n && sum + bit[pos + next] < val)
            {
                sum += bit[pos + next];
                pos += next;
            }
        }

        return pos + 1;
    }
};


Fenwick tree;

int question (int x, int k);

int binary(int m)
{
    int lPtr = 0, rPtr = m;

    while (rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        int kth_first = tree.find_kth(mid);
        int kth_second = question(m, mid);

        if(kth_first == kth_second)
        {
            lPtr = mid;
        }
        else
        {
            rPtr = mid;
        }
    }

    return rPtr;
}


std::vector <int> solve (int N)
{
    n = N;

    tree.set();

    for(int i = 1 ; i <= n ; ++i)
    {
        int idx = binary(i);
        //cout << "idx : " << idx << "\n";
        int number = question(i, idx);

        v.push_back(number);

        tree.update(number, +1);
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
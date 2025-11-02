#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long llong;

const int MAXN = 16;
const llong INF = 1e18;

int n, k;
int p[MAXN];
vector<int> lPrimes, rPrimes;
vector<llong> lProducts, rProducts;

llong f(llong x) {
    llong cnt = 0;

    int j = (int)rProducts.size() - 1;         
    
    for (llong l : lProducts)
    {
        if (l > x) break;

        llong t = x / l;
        
        cnt += upper_bound(rProducts.begin(), rProducts.end(), t) - rProducts.begin();
        
        if (cnt >= k) return k;
    }
    
    return min<llong>(cnt, k);
}

llong binary()
{
    cout << "Binary" << "\n";
    
    llong l = -1, r = INF + 1;

    while(r > l + 1)
    {
        llong m = l + (r - l) / 2;

        if(f(m) >= k) r = m;
        else l = m;
    }

    return r;
}

void calc(vector<int>& primes, vector<llong>& out)
{
    cout << "Recursion" << "\n";

    int sz = primes.size();

    function<void(int, llong)> rec = [&](int i, llong cur)
    {
        cout << i << " " << cur << "\n";
        if(i == sz)
        {
            out.push_back(cur);
            cout << "->" << cur << "\n";
            return;
        }

        llong v = cur;

        while(true)
        {
            rec(i + 1, v);

            if(primes[i] == 1) break;
            if(v * primes[i] > 100) break;

            v *= primes[i];
        }
    };

    rec(0, 1);

    sort(out.begin(), out.end());
}

void solve()
{
    cin >> n;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> p[i];
    }

    cin >> k;
    

    for(int i = 0 ; i < n ; ++i)
    {
        if(i % 2 == 0)
        {
            lPrimes.push_back(p[i]);
        }
        else
        {
            rPrimes.push_back(p[i]);
        }
    }

    cout << "lPrimes" << "\n";

    for(llong lp : lPrimes)
    {
        cout << lp << " ";
    }

    cout << "\n";
    cout << "rPrimes" << "\n";

    for(llong rp : rPrimes)
    {
        cout << rp << " ";
    }
    cout << "\n";

    calc(lPrimes, lProducts);
    calc(rPrimes, rProducts);

    cout << "lProducts" << "\n";

    for(llong lp : lProducts)
    {
        cout << lp << " ";
    }

    cout << "\n";
    cout << "rProducts" << "\n";

    for(llong rp : rProducts)
    {
        cout << rp << " ";
    }
    cout << "\n";

    //cout << binary() << "\n";
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
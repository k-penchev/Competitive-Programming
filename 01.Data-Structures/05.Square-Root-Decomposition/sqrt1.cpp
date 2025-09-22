#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000 + 10;
const int BUCKET_SIZE = 320;
const int BUCKET_COUNT = 320;

int n, q, a[MAXN];
int buckets[BUCKET_COUNT];          

inline int block_index(int i) { return (i - 1) / BUCKET_SIZE + 1; }          
inline int L(int b)   { return (b - 1) * BUCKET_SIZE + 1; }          
inline int R(int b)   { return min(n, b * BUCKET_SIZE); }            

void build()
{
    for (int i = 1; i <= n; ++i) buckets[block_index(i)] += a[i];
}

void update(int pos, int val)
{
    a[pos] += val;
    buckets[block_index(pos)] += val;
}

long long query(int l, int r)
{
    
    int lb = block_index(l), rb = block_index(r);
    long long sum = 0;

    if (lb == rb)
    {
        for (int i = l; i <= r; ++i) sum += a[i];
        return sum;
    }

    for (int i = l; i <= R(lb); ++i) sum += a[i];
    
    for (int b = lb + 1; b <= rb - 1; ++b) sum += buckets[b];
    
    for (int i = L(rb); i <= r; ++i) sum += a[i];

    return sum;
}

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
    }

    build();

    int qType, x, y;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> qType >> x >> y;

        if(qType == 1)
        {
            update(x, y);
        }
        else
        {       
            cout << query(x, y) << "\n";
        }   
    }
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
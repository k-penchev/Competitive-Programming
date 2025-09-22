#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;
const int BUCKET_SIZE = 320;
const int BUCKET_COUNT = 320; 

int n, q, a[MAXN];
int inBucket[MAXN];

struct Bucket {
    int l, r;
    long long prefix[BUCKET_SIZE + 2]; 

    int len()
    { 
        return r - l + 1; 
    }

    long long query(int l, int r)
    {
        return prefix[r] - prefix[l - 1];
    }

    void rebuild()
    {
        prefix[0] = 0;
        int k = 0;
        for (int i = l; i <= r; ++i)
        {
            prefix[++k] = prefix[k - 1] + a[i];
        }
    }

    void addPoint(int pos, int delta)
    {
        int loc = pos - l + 1;                   
        for (int k = loc; k <= len(); ++k)
        {
            prefix[k] += delta;
        }
    }
};

long long global_prefix[BUCKET_COUNT + 5];
Bucket bucket[BUCKET_COUNT + 5];


void solve()
{
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int cntBuckets = 0;
    global_prefix[0] = 0;

    for (int i = 1; i <= n; i += BUCKET_SIZE)
    {
        int l = i;
        int r = min(n, i + BUCKET_SIZE - 1);
        ++cntBuckets;

        bucket[cntBuckets].l = l;
        bucket[cntBuckets].r = r;
        bucket[cntBuckets].rebuild();

        for (int j = l; j <= r; ++j)
        {            
            inBucket[j] = cntBuckets;
        }

        long long bsum = bucket[cntBuckets].prefix[bucket[cntBuckets].len()];
        global_prefix[cntBuckets] = global_prefix[cntBuckets - 1] + bsum;
    }

    while (q--)
    {
        int qType, x, y;
        cin >> qType >> x >> y;

        if (qType == 1)
        {

            int b = inBucket[x];
            a[x] += y;
            bucket[b].addPoint(x, y);
            for (int t = b; t <= cntBuckets; ++t) global_prefix[t] += y;

        }
        else
        {
            
            int l = x, r = y;
            int lb = inBucket[l], rb = inBucket[r];

            long long ans = 0;
            if (lb == rb)
            {
                
                int Lloc = l - bucket[lb].l + 1;
                int Rloc = r - bucket[lb].l + 1;
                ans = bucket[lb].query(Lloc, Rloc);

            }
            else
            {

                int Lloc = l - bucket[lb].l + 1;
                ans += bucket[lb].query(Lloc, bucket[lb].len());

                int Rloc = r - bucket[rb].l + 1;
                ans += bucket[rb].query(1, Rloc);

                if (rb >= lb + 2)
                {
                    ans += global_prefix[rb - 1] - global_prefix[lb];
                }

            }
            cout << ans << "\n";
        }
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main() {
    fastIO();
    solve();
    return 0;
}

#include <algorithm>
#include <iostream>
#include <cassert>
#include <numeric>
#include <random>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>

const int MAXN = 200000 + 10;
const int BUCKET_SIZE = 450;
const int BUCKET_COUNT = 450;

int n, q;
int a[MAXN];

namespace Decomposition
{
    struct Bucket
    {
        int l, r;
        int cpy[BUCKET_SIZE + 1];
        int cnt;
        int sum;

        void build()
        {
            cnt = r - l + 1;
            for(int i = l, j = 1 ; i <= r ; ++i, ++j)
            {
                cpy[j] = a[i];
                sum += cpy[j];
            }
        }

        void update(int queryPos, int queryVal)
        {
            sum -= cpy[queryPos];
            cpy[queryPos] = queryVal;
            sum += cpy[queryPos];
        }

        int query(int queryL, int queryR)
        {
            int res = 0;
            for(int i = queryL ; i <= queryR ; ++i)
            {
                res += cpy[i];
            }
            return res;
        }
    };

    int inBucket[MAXN];
    Bucket bucket[BUCKET_COUNT];

    void build()
    {
        int cntBuckets = 0;
        for(int i = 1 ; i <= n ; i += BUCKET_SIZE)
        {
            int l = i;
            int r = std::min(n, i + BUCKET_SIZE - 1);
            cntBuckets++;

            bucket[cntBuckets].l = l;
            bucket[cntBuckets].r = r;
            bucket[cntBuckets].build();
            for (int j = l ; j <= r ; ++j)
            {
                inBucket[j] = cntBuckets;
            }
        }
    }

    void update(int queryPos, int queryVal) 
    {
        int localPos = queryPos - bucket[inBucket[queryPos]].l + 1;
        bucket[inBucket[queryPos]].update(localPos, queryVal);
    }

    int query(int queryL, int queryR)
    {
        int res = 0;
        int bucketL = inBucket[queryL];
        int bucketR = inBucket[queryR];

        int localL = queryL - bucket[bucketL].l + 1;
        int localR = queryR - bucket[bucketR].l + 1;

        if(bucketL == bucketR)
        {
            res += bucket[bucketL].query(localL, localR);
        }
        else
        {
            res += bucket[bucketL].query(localL, bucket[bucketL].cnt);
            for(int i = bucketL + 1 ; i < bucketR ; ++i)
            {
                res += bucket[i].sum;
            }
            res += bucket[bucketR].query(1, localR);
        }

        return res;
    }

};

void solve()
{
    std::cin >> n >> q;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    Decomposition::build();
    for(int i = 1 ; i <= q ; ++i)
    {
        int type, x, y;
        std::cin >> type >> x >> y;
        
        if(type == 1)
        {
            Decomposition::update(x, y);
        }
        else
        {
            std::cout << Decomposition::query(x, y) << "\n";
        }
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
    solve();
    
    return 0;
}
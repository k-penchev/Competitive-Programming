#include <bits/stdc++.h>

using namespace std;

const int MAXN         = 3 * 1e5 + 10; 
const int BUCKET_SIZE  = 550;
const int BUCKET_COUNT = 550;


struct Query
{
    int l, r;
    int k;
    int idx;
};

int n, q;
int a[MAXN], b[MAXN], ans[MAXN];
Query queries[MAXN];
int cnt = 0;


void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
    }

    int l, r, x;

    for(int i = 1 ; i <= q ; ++i)
    {   
        cin >> l >> r >> x;
        queries[i].l = l;
        queries[i].r = r;
        queries[i].k = (r - l + 1) / x;
        queries[i].idx = i;
    }

    sort(queries + 1, queries + q + 1, [&](const Query& q1, const Query& q2){
        
        if(q1.l / BUCKET_COUNT == q2.l / BUCKET_COUNT)
        {
            return q1.r < q2.r;
        }
        
        return ( (q1.l / BUCKET_COUNT) < (q2.l / BUCKET_COUNT) );
    });


    int lPtr = 1, rPtr = 0;

    for(int i = 1 ; i <= q ; ++i)
    {
        auto [L, R, K, idx] = queries[i];

        while(lPtr > L)
        {
            --lPtr;
            //add
        }

        while(rPtr < R)
        {
            ++rPtr;
            //add
        }

        while(lPtr < L)
        {
            //remove
            lPtr++;
        }

        while(rPtr > R)
        {
            //remove
            rPtr--;
        }

        // ans[idx] = cnt;
    }

    for(int i = 1 ; i < q ; ++i)
    {
        cout << ans[i] << "\n";
    }

}

void fastIO()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main()
{
    fastIO();
    solve();
}

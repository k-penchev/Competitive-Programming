#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5; 

struct Query {
    int l, r, idx;
};

int n, q;
int a[MAXN], b[MAXN];
pair<int, int> toCompress[MAXN];
Query qs[MAXN];
int freq[MAXN];
long long cnt = 0;
long long ans[MAXN];

inline void add_pos(int p) {
    int x = b[p];
    if (++freq[x] == 1) ++cnt; 
}
inline void remove_pos(int p) {
    int x = b[p];
    if (--freq[x] == 0) --cnt; 
}

void compress()
{
    sort(toCompress + 1, toCompress + n + 1);

    int max_number = 0;

    for(int i = 1 ; i <= n ; ++i)
    {
        max_number += (toCompress[i].first != toCompress[i - 1].first);
        b[toCompress[i].second] = max_number;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }

    for(int i = 1; i <= n; ++i)
    {
        toCompress[i] = {a[i], i};
    }

    compress();

    cin >> q;
    for (int i = 1; i <= q; ++i) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].idx = i;
    }

    int B = max(1, (int)sqrt(n));
    sort(qs + 1, qs + q + 1, [&](const Query& A, const Query& Bq) {
        int blA = A.l / B, blB = Bq.l / B;
        if (blA != blB) return blA < blB;
        return A.r < Bq.r;
    });

    int curL = 1, curR = 0; 
    for (int i = 1; i <= q; ++i) {
        int L = qs[i].l, R = qs[i].r, id = qs[i].idx;
        while (curL > L) add_pos(--curL);
        while (curR < R) add_pos(++curR);
        while (curL < L) remove_pos(curL++);
        while (curR > R) remove_pos(curR--);
        ans[id] = cnt; 
    }

    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}

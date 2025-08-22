#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

int n;
int a[MAXN];

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
    }

    /*
    Goal:
      Partition the sequence a[1..n] into the MINIMUM number of monotone subsequences
      of a chosen type X. (“Cover” here means a partition: every element belongs to
      exactly one subsequence.)

    Key fact (Dilworth/Mirsky + patience sorting):
      The minimum number of subsequences of type X needed to cover the array equals
      the length of the “opposite” longest subsequence Y, with strictness flipped.

    Mapping (X -> minimal # equals length of Y):
      1) X = non-increasing (>=)         -> Y = LIS_strict (strictly increasing)
      2) X = non-decreasing (<=)         -> Y = LDS_strict (strictly decreasing)
      3) X = strictly decreasing (>)     -> Y = LNDS      (longest non-decreasing)
      4) X = strictly increasing (<)     -> Y = LNIS      (longest non-increasing)

    Notes:
      • “Strict” uses < or >; “non-strict” uses <= or >=.
      • For implementation, lengths can be found in O(n log n) via patience sorting:
        - strict LIS/LDS: use lower_bound; for LDS, apply to -a[i].
        - non-strict variants: use upper_bound (or adjust ties carefully).
    */
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

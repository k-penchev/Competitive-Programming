#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 100000 + 5;
const int NINF = (int)-4e18;
const int PINF = (int) 4e18;

int n;
int a[MAXN];
int dp[MAXN]; 

// first index i with dp[i] >= x   (lower_bound)
int lower_binary_search(int x){
    int l = 0, r = n;                // invariant: dp[l] < x, dp[r] >= x
    while (r > l + 1){
        int m = (l + r) >> 1;
        if (dp[m] >= x) r = m; else l = m;
    }
    return r;                        // in [1..n]
}

// first index i with dp[i] > x     (upper_bound)
int upper_binary_search(int x){
    int l = 0, r = n;                // invariant: dp[l] <= x, dp[r] > x
    while (r > l + 1){
        int m = (l + r) >> 1;
        if (dp[m] > x) r = m; else l = m;
    }
    return r;                        // in [1..n]
}

inline void reset(){
    for (int i = 0; i <= n; ++i) dp[i] = PINF;
    dp[0] = NINF;
}

inline int compute_answer(){
    int ans = 0;
    while (ans < n && dp[ans + 1] < PINF) ++ans;
    return ans;
}

int strict_lis(){
    reset();
    for (int i = 0; i < n; ++i){
        int pos = lower_binary_search(a[i]); // first >= a[i]
        dp[pos] = a[i];
    }
    return compute_answer();
}

int strict_lds(){
    reset();
    for (int i = 0; i < n; ++i){
        int x = -a[i];
        int pos = lower_binary_search(x);    // LIS on -a
        dp[pos] = x;
    }
    return compute_answer();
}

int non_strict_lis(){
    reset();
    for (int i = 0; i < n; ++i){
        int pos = upper_binary_search(a[i]); // first > a[i]
        dp[pos] = a[i];
    }
    return compute_answer();
}

int non_strict_lds(){
    reset();
    for (int i = 0; i < n; ++i){
        int x = -a[i];
        int pos = upper_binary_search(x);    // non-inc on a == non-dec on -a
        dp[pos] = x;
    }
    return compute_answer();
}


void solve()
{
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    cout << "Strict LIS : " << strict_lis() << "\n";
    cout << "Strict LDS : " << strict_lds() << "\n";
    cout << "Non - strict LIS : " << non_strict_lis() << "\n";
    cout << "Non - strict LDS : " << non_strict_lds() << "\n";
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
}

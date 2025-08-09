#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 5e5 + 2;

int n;
int nums[2 * MAXN], r[2 * MAXN];

struct Fenwick {
    
    int bit[2 * MAXN];

    void reset(){
        for(int i = 0 ; i <= 2 * n ; i++){
            bit[i] = 0;
        }
    }

    void update(int idx, int val){
        while(idx <= 2 * n){
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int query(int idx){
        int sum = 0;

        while(idx > 0){
            sum += bit[idx];
            idx -= idx & (-idx);
        }

        return sum;
    }
};

Fenwick tree;
long long swaps;

void solve(){
    cin >> n;

    for(int i = 1 ; i <= 2 * n ; ++i){
        cin >> nums[i];
    }

    for(int i = 2 * n ; i >= 1 ; --i){
        if(r[nums[i]] == 0){
            r[nums[i]] = i;
        }
    }

    tree.reset();

    for(int i = 1 ; i <= 2 * n ; ++i){
        if(r[nums[i]] != 0){
            swaps += tree.query(r[nums[i]]);
            tree.update(r[nums[i]], +1);
            r[nums[i]] = 0;
        }
        else{
            tree.update(i, -1);
        }
    }

    cout << swaps + n << '\n';
}

void fastIO(){
    ios :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main(){
    fastIO();
    solve();
}
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e6 + 5;

struct Fenwick {
    
    int bit[MAXN];

    void reset(){
        for(int i = 0 ; i <= MAXN ; i++){
            bit[i] = 0;
        }
    }

    void update(int idx, int val){
        while(idx <= MAXN){
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

void solve(){
    tree.reset();
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
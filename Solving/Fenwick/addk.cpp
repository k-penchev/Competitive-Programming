#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 2;

int n, k, q;
int nums[MAXN];

struct Fenwick {
    
    int bit[MAXN];

    void reset(){
        for(int i = 0 ; i < n ; i++){
            bit[i] = 0;
        }
    }

    void update(int idx, int val){
        while(idx <= n){
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

Fenwick tree1;
Fenwick tree2;

void handle_update(){
    int indecies[k + 1];

    for(int i = 1 ; i <= k ; ++i){
        cin >> indecies[i];
    }

    int head = nums[indecies[1]];

    for(int i = 1 ; i <= k - 1 ; ++i){
        int old_value = nums[indecies[i]];
        int new_value = nums[indecies[i + 1]];
        tree1.update(indecies[i], new_value -  old_value);
        tree2.update(indecies[i], indecies[i] * (new_value - old_value));
        nums[indecies[i]] = nums[indecies[i + 1]];
    }

    tree1.update(indecies[k], head - nums[indecies[k]]);
    tree2.update(indecies[k], indecies[k] * (head - nums[indecies[k]]));
    nums[indecies[k]] = head;
}

long long compute_query() {
    int l, r, m;
    cin >> l >> r >> m;

    long long segSum = tree1.query(r) - tree1.query(l-1);   // Σ a[p]
    long long ans    = 1LL * m * segSum;                    // m · Σ a[p]

    if (m == 1) return ans;         // no ends to subtract

    int len = m - 1;

    /* left block */
    long long LeftSum     = tree1.query(l + len - 1) - tree1.query(l - 1);
    long long LeftSumIdx  = tree2.query(l + len - 1) - tree2.query(l - 1);
    ans -= (1LL * (len + l) * LeftSum - LeftSumIdx);

    /* right block */
    long long RightSum    = tree1.query(r) - tree1.query(r - len);
    long long RightSumIdx = tree2.query(r) - tree2.query(r - len);
    ans -= (1LL * (len - r) * RightSum + RightSumIdx);

    return ans;
}



void solve(){
    cin >> n >> k;

    for(int i = 1 ; i <= n ; ++i){
        cin >> nums[i];
        tree1.update(i, nums[i]);
        tree2.update(i, nums[i] * i);
    }

    cin >> q;

    int type;   

    while(q--){
        cin >> type;

        if(type == 1) { 
            handle_update();
        } 
        else {
            cout << compute_query() << endl;
        }

    }
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
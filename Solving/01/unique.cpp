#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 2;

int n, q;

struct Fenwick {
    
    int bit[MAXN];

    void reset(){
        for(int i = 0 ; i <= n ; i++){
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

Fenwick tree;
vector<int> nums, compressed;
vector<bool> marked;

void compress(){
    vector<int> sorted = nums;  
    sort(sorted.begin(), sorted.end()); 
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());  

    compressed.resize(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        compressed[i] = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin() + 1;
    }
}

void solve(){
    cin >> n;

    for(int i = 1 ; i <= n ; ++i){
        int x; cin >> x;
        nums.push_back(x);
    }

    compress();

    marked.resize(compressed.size());

    fill(marked.begin(), marked.end(), false);

    for(int c : compressed){
        if(!marked[c]){
            tree.update(c, +1);
            //cout << "marking " << c << endl;
        }
        marked[c] = true;
    }
    //cout << endl;
    
    cin >> q;

    while(q--){
        int l, r; cin >> l >> r;
        cout << tree.query(r) - tree.query(l - 1) << '\n';
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
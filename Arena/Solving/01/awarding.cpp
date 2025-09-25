#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e6 + 5;
const int MAXLOG = 21;

int n;
long long a[MAXN], b[MAXN], c[MAXN];
long long sorted[MAXN];

struct Fenwick{

    int bit[MAXN];

    void init(){
        for(int i = 1; i <= n; ++i){
            bit[i] = 0;
        }
    }

    void update(int idx, int val){
        while(idx <= n){
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int search(int val){
        int pos = 0, sum = 0;

        for(int i = MAXLOG - 1; i >= 0; --i){
            if(pos + (1 << i) < n && sum + bit[pos + (1 << i)] < val){
                sum += bit[pos + (1 << i)];
                pos += (1 << i);
            }
        }

        return pos + 1;
    }
};

Fenwick tree;

bool compare(int x, int y){
    return c[x] < c[y];
}

void solve(){
    iota(sorted + 1, sorted + n + 1, 1);
    sort(sorted + 1, sorted + n + 1, compare);

    for(int i = 1; i <= n; ++i) b[sorted[i]] = i;

    tree.init();

    for(int i = 1; i <= n; ++i){
        tree.update(i, +1);
    }

    for(int i = 1; i <= n; ++i){
        a[sorted[i]] = tree.search(1 + c[sorted[i]] - c[sorted[i - 1]]);
        tree.update(a[sorted[i]], -1);
    }

    for(int i = 1; i <= n; ++i){
        cout << a[i] << " "; 
    }

    cout << '\n';


    for(int i = 1; i <= n; ++i){
        cout << b[i] << " "; 
    }

    cout << '\n';
}

void input(){
    cin >> n; 

    for(int i = 1; i <= n; ++i){
        cin >> c[i];
    }
}

void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main(){
    fastIO();
    input();
    solve();
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXLOG = 21;

struct Fenwick {
    
    int bit[MAXN];

    void reset(){
        for(int i = 0 ; i < MAXN ; i++){
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

    int bit_search(int v){
        int sum = 0;
        int pos = 0;

        for(int i = MAXLOG; i >= 0; --i){
            if( (pos + (1 << i) < MAXN ) && ( sum + bit[pos + (1 << i)] < v )){
                sum += bit[pos + (1 << i)];
                pos += (1 << i);
            }
        }

        return pos + 1;
    }

};

Fenwick tree;

void test(){
    tree.reset();

    for(int i = 1; i <= 10; i++){
        tree.update(i, i);
    }

    cout << tree.query(5) << endl;
    cout << tree.bit_search(15) << endl;
    cout << tree.bit_search(22) << endl;
}

int main(){
    test();
    return 0;
}
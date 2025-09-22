#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;
const int MAXLOG = 21;

int n;

struct Fenwick_1 {
    
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

    int bit_search(int v){
        cout << "Entering 1" << endl;
        int sum = 0;
        int pos = 0;

        for(int i = MAXLOG; i >= 0; --i){
            cout << "i=" << i << endl;
            //cout << "pos + (1 << i)=" << pos + (1 << i) << endl;
            if( (pos + (1 << i) < n ) && ( sum + bit[pos + (1 << i)] < v )){
                sum += bit[pos + (1 << i)];
                pos += (1 << i);
                cout << "sum=" << sum << endl;
            }
        }

        return pos + 1;
    }

};

struct Fenwick_2{
    int tree[MAXN];
    void update(int idx, int val)
    {
        for (; idx <= n + 1 ; idx += idx & (-idx))
        {
            tree[idx] += val;
        }
    }

    int query(int idx)
    {
        int res = 0;
        for (; idx ; idx -= idx & (-idx))
        {
            res += tree[idx];
        }

        return res;
    }

    int findKth(int k)
    {
        cout << "Entering 2" << endl;
        cout << "NOTE K=" << k << endl;
        int idx = 0;
        for (int lg = MAXLOG - 1 ; lg >= 0 ; --lg)
        {
            cout << "i=" << lg << endl;
            if (idx + (1 << lg) <= n + 1 && tree[idx + (1 << lg)] < k)
            {
                idx += (1 << lg);
                k -= tree[idx];
                cout << "k=" << k << endl;
            }
        }

        return idx + 1;
    }
};

struct Fenwick_3{
    int tree[MAXN];
    void update(int idx, int val)
    {
        for (int pos = idx ; pos <= n ; pos += pos & (-pos))
        {
            tree[pos] += val;
        }
    }

    int findKth(int kth)
    {
        cout << "Entering 3" << endl;
        cout << "NOTE KTH=" << kth << endl;
        int pos = 0;
        for (int lg = MAXLOG - 1 ; lg >= 0 ; --lg)
        {
            cout << "i=" << lg << endl;
            if (pos + (1 << lg) <= n && (1 << lg) - tree[pos + (1 << lg)] < kth)
            {
                pos += (1 << lg);
                kth -= (1 << lg) - tree[pos];
                cout << "kth=" << kth << endl;
            }
        }   

        return pos + 1;
    }
};

Fenwick_1 tree1;
Fenwick_2 tree2;
Fenwick_3 tree3; // returning the kth 0 position

void test(){
    
    n = 10;

    for(int i = 1; i <= n; i++){
        tree1.update(i, i);
        tree2.update(i, i);
    }

    int a = tree1.bit_search(27);
    int b = tree2.findKth(27);
    cout << a << " " << b << endl;
}

int main(){
    test();
    return 0;
}
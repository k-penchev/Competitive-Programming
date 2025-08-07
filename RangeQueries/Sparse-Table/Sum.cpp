#include <bits/stdc++.h>

using namespace std;

const int n = 10;
const int k = 3;

int arr[n];
int st[k + 1][30];

int sum(int l, int r){
    long long sum = 0;
    return 0;
}

int main(){
    for(int i = 0; i < 10; i++){
        arr[i] = i + 1;
    }

    for(int i = 0; i < 10; i++){
        st[0][i] = arr[i];
    }

    for (int i = 1; i <= k; i++){
        for (int j = 0; j + (1 << i) <= n; j++){
            st[i][j] = st[i - 1][j] + st[i - 1][j + (1 << (i - 1))];
            cout << st[i][j] << " ";
        }

        cout << "\n";
    }
        
}
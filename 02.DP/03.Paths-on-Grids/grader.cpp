#include "grid.h"
#include<iostream>
#include<vector>
using namespace std;
int main () {
    int n, m, c;
    cin >> n >> m >> c;
    vector<vector<int>> inp(n, vector<int>(m));
    for(int i = 0; i < n; i ++){
    	for(int j = 0; j < m; j ++){
    		cin >> inp[i][j];
    	}
    }
    long long ans = max_profit(n, m, c, inp);
    cout << ans << endl;
    return 0;
}

#include<bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;


ll qry(const vector<ll>& BIT, int idx) {
    ll sum = 0;
    while (idx > 0) {
        sum += BIT[idx];
        idx -= idx & -idx; 
    }
    return sum;
}


void upd(vector<ll>& BIT, int idx, ll val) {
    while (idx < BIT.size()) { 
        BIT[idx] += val;
        idx += idx & -idx; 
    }
}


vector<int> compress_coordinates(const vector<ll>& arr) {
    vector<ll> sorted = arr; 
    sort(sorted.begin(), sorted.end()); 
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end()); 

    vector<int> compressed(arr.size());
    for (size_t i = 0; i < arr.size(); ++i) {
        compressed[i] = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin() + 1;
    }
    return compressed;
}

void fastIO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

int main() {
    fastIO();

    ll n; 
    cin >> n;

    vector<ll> arr(n);
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
    }

    
    vector<int> compressed = compress_coordinates(arr);
    int max_val = *max_element(compressed.begin(), compressed.end());

    
    vector<ll> BIT(max_val + 1, 0);

    ll inversions = 0;

    
    for (int i = compressed.size() - 1; i >= 0; --i) {
        
        inversions += qry(BIT, compressed[i] - 1);

        
        upd(BIT, compressed[i], 1);
    }

    cout << inversions << endl;

    return 0;
}

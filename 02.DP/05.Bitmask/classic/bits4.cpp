//Bit optimizations
#include <bits/stdc++.h>

using namespace std;

int hamming_distance(int a, int b)
{
    return __builtin_popcount(a ^ b);
}

void solve()
{
    vector<int> strings = {
        12, // 001100
        25, // 011001
        24, // 011000
        39  // 100111
    };


    for(int i = 0 ; i < strings.size() ; ++i)
    {
        for(int j = i + 1 ; j < strings.size() ; ++j)
        {
            cout << hamming_distance(strings[i], strings[j]) << "\n";
        }
    }

}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
//Bit operations
#include <bits/stdc++.h>

using namespace std;

void print_in_binary(int num)
{
    for(int bit = 31 ; bit >= 0 ; --bit)
    {
        if(num & (1 << bit)) cout << "1";
        else cout << "0";
    }

    cout << " " << num << "\n";
}

void solve()
{
    int x = 5, y = 10;

    cout << (x & y) << "\n";
    cout << (x | y) << "\n";
    cout << (x ^ y) << "\n";
    cout << (~x) << "\n"; // the same as (-x - 1)

    int k = 2;
    cout << (x << k) << "\n"; // the same as x * (2^k)
    cout << (x >> k) << "\n"; // the same as floor( x / (2^k) )

    print_in_binary(5);

    /*
    
    x & (1 << k)  -> return the kth bit of x
    x | (1 << k)  -> sets the kth bit of x to 1
    x ^ (1 << k)  -> flips the kth bit of x
    x & ~(1 << k) -> sets the kth bit of x to 0
    x & (x - 1)   -> sets the last one bit of x to zero
    x & -x        -> sets all the one bits to zero, except for the last one bit
    x | (x - 1)   -> inverts all the bits after the last one bit
    
    
    x & 1 -> 0 means x is even ; 1 means x is odd
    x & ( (1 << k) - 1) -> checks if x is devisible by (1 << k)
    x & (x - 1) -> if x is positive and the condition is 0, then x is power of 2

    __builtin_clz(x) -> leading zeros
    __builtin_ctz(x) -> ending zeros
    __builtin_popcount(x) -> number of 1s
    __builtin_parity(x) -> parity of the number of ones

    * When the number is 'long long' -> add suffix ll

    */


    x = 5328; // 00000000000000000001010011010000
    cout << __builtin_clz(x) << "\n"; // 19
    cout << __builtin_ctz(x) << "\n"; // 4
    cout << __builtin_popcount(x) << "\n"; // 5
    cout << __builtin_parity(x) << "\n"; // 1

    print_in_binary((1 << 30));
    print_in_binary((1 << 30) - 1);

    /*subset = (subset - 1) & mask

    cout << "\n";
    cout << "\n";

    int set = 282; // {1, 3, 4, 8}

    for (int subset = set; ; subset = (subset - 1) & set)
    {
        print_in_binary(subset);

        if (subset == 0) break;
    }

    cout << "\n";
    cout << "\n";

    int subset = 0;

    do
    {
        print_in_binary(subset);
    }
    while(subset = (subset - set) & set);

    cout << "\n";
    cout << "\n";*/
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
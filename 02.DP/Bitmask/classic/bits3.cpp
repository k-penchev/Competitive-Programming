//Representing sets
#include <bits/stdc++.h>

using namespace std;

void iterate_everything(int maxElement)
{
    for(int mask = 0 ; mask < (1 << maxElement) ; ++mask)
    {
        //process subset (s1) under "mask"

        for(int submask = mask ; submask != 0 ; submask = (submask - 1) & mask)
        {
            //process strict subset(s2) of (s1) under "submask"

            int strict_subset = mask ^ submask;
        }
    }
}

void iterate_over_decreasing_strict_subsets(int mask)
{
    for(int submask = mask; ; submask = (submask - 1) & mask)
    {
        cout << submask << " ";

        if (submask == 0) break;   // includes empty set at the end
    }

    cout << "\n";
}

void iterate_over_increasing_strict_subsets(int mask)
{
    int submask = 0;
    
    do
    {
        cout << submask << " ";
    }
    while(submask = (submask - mask) & mask);

    cout << "\n";
}

void iterate_through_subsets_of_size_k(int maxElement, int k)
{
    for(int mask = 0 ; mask < (1 << maxElement) ; ++mask)
    {
        if(__builtin_popcount(mask) == k)
        {
            //process subset
        }
    }
}

void iterate_through_subsets(int maxElement)
{
    for(int mask = 0 ; mask < (1 << maxElement); ++mask) // 2^n
    {
        //process subset 
    }
}

void print_set(int set)
{
    for(int num = 0 ; num < 32 ; ++num)
    {
        if(set & (1 << num))
        {
            cout << num << " ";
        }
    }

    cout << "\n";
}

void solve()
{
    
    int setA = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 8);
    int setB = (1 << 1) | (1 << 6) | (1 << 8);

    iterate_over_decreasing_strict_subsets(setA);
    iterate_over_increasing_strict_subsets(setA);

    print_set(setA);
    print_set(setB);

    int setC1 = setA & setB;    // intersection
    int setC2 = setA | setB;    // union
    int setC3 = ~setA;          // complement
    int setC4 = setA & (~setB); // difference

    print_set(setC1);
    print_set(setC2);
    print_set(setC3);
    print_set(setC4);
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
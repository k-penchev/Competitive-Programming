#include <bits/stdc++.h>

using namespace std;

int get_lis_length(const std::vector<int>& p);

int find_maximum(int n)
{
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);

    int lisLenBefore = 0, lisLenAfter = 0, idx = 0;

    do
    {
        lisLenBefore = get_lis_length(perm);


        if(lisLenBefore == n)
        {
            idx = perm[n - 1];
            break;
        }

        swap(perm[0], perm[n - 1]);

        lisLenAfter = get_lis_length(perm);

        if(lisLenBefore == lisLenAfter + 1)
        {
            idx = perm[0];
            break;
        }

        shuffle(perm.begin(), perm.end(), std::mt19937{std::random_device{}()});
    }
    while(true);

    return idx;
}
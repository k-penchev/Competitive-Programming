#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ordered_set = tree <int, null_type, less<int> , rb_tree_tag, tree_order_statistics_node_update>; 

void solve()
{
    ordered_set o_set;

    o_set.insert(1);
    o_set.insert(2);
    o_set.insert(4);
    o_set.insert(10);

    //*o_set.find_by_order(2); -> value of the Xth element
    //o_set.order_of_key(3); -> number of strictly smaller elements compared to X
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
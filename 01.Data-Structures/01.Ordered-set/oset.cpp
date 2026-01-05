#include <iostream>
#include <algorithm>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

using OrderedSet = tree<int, null_type, std::less<int> , rb_tree_tag, tree_order_statistics_node_update>; 

void solve()
{
    OrderedSet o_set;

    o_set.insert(1);
    o_set.insert(2);
    o_set.insert(4);
    o_set.insert(10);

    //*o_set.find_by_order(2); -> value of the 2-nd element
    //o_set.order_of_key(3); -> number of strictly smaller elements compared to 3
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
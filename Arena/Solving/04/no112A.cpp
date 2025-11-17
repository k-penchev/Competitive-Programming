#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

const int MAXN = 1e5 + 10;

int n, m, q;
std::vector<std::pair<int, int>> graph;
std::unordered_map<std::pair<int, int>, int> map;
std::vector<int> query;

struct DSU
{

};

DSU dsu;

struct SegmentTree
{

};

SegmentTree tree;

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        if(a > b) std::swap(a, b);
        graph.push_back({a, b});
    }

    std::cin >> q;

    for(auto &[a, b] : graph)
    {
        tree.update(a, b, 1, q);
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int type, a, b;
        std::cin >> type >> a >> b;
        if(a > b) std::swap(a, b);

        if(type == 1)
        {
            query.push_back(i);
        }
        else if(type == 2)
        {
            map[{a, b}] = i;
        }
        else
        {
            tree.update(map[{a, b}], i - 1, a, b);
            map.erase({a, b});
        }
    }

    for(auto &[key, value] : map)
    {
        tree.update(value, q, key.first, key.second);
    }

    dsu.set();
    tree.dfs();

    int ptr = 0;
    for(int i = 1 ; i <= q ; ++i)
    {
        if(ptr < query.size() && query[ptr] == i)
        {
            ptr += 1;
            std::cout << ans[i];
        }
    }

    std::cout << "\n";
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
    
    return 0;
}
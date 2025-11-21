//wrong solution
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

const int MAXN = 2 * 1e5 + 10;

int t, n;

struct Edge
{
    int to;
    int idx;
};

int id = 1;
std::pair<int, int> edge[MAXN];
std::vector<Edge> g[MAXN];
std::unordered_map<int, int> map;
std::vector<int> path;
int deg[MAXN];
bool visited[MAXN];

void euler(int node, int edge)
{
    while(g[node].size())
    {
        auto [to, idx] = g[node].back();
        g[node].pop_back();

        if(visited[idx])
        {
            continue;
        }

        visited[idx] = 1;
        euler(to, idx);
    }

    path.push_back(edge);
}

void reset()
{
    id = 1;
    for(auto &adj : g)
    {
        adj.clear();
    }

    path.clear();
    map.clear();
    std::fill(deg + 1, deg + n + 1, 0);
    std::fill(visited + 1, visited + n + 1, 0);
}

void fail()
{
    std::cout << "NO" << "\n";
    reset();
}

void solve()
{
    std::cin >> t;

    for(int test = 1 ; test <= t ; ++test)
    {
        std::cin >> n;

        for(int i = 1 ; i <= n ; ++i)
        {
            int a, b;
            std::cin >> a >> b;

            if(!map.count(a)) map[a] = id++;
            if(!map.count(b)) map[b] = id++;
            

            edge[i] = {map[a], map[b]};
            g[map[a]].push_back({map[b], i});
            g[map[b]].push_back({map[a], i});
            deg[map[a]] += 1, deg[map[b]] += 1;
        }

        int start = -1, odd = 0;
        for(auto &[node, id] : map)
        {
            if(deg[id] % 2 != 0)
            {
                odd += 1;
                start = id;
            }

            if(deg[id] > 0 && start == -1)
            {
                start = id;
            }
        }

        if(!(odd == 0 || odd == 2))
        {
            fail();
            continue;
        }

        euler(start, -1);
        
        path.pop_back();
        std::reverse(path.begin(), path.end());

        bool failed = false;
        for(int i = 0 ; i < path.size() ; ++i)
        {
            int current = i;
            int first = i + 1;
            int second = i + 2;

            if(first == path.size())
            {
                break;
            }

            auto &[u1, v1] = edge[current];
            auto &[u2, v2] = edge[first];
            auto &[u3, v3] = edge[second];

            if((u1 == u2 == u3) || (v1 == v2 == v3))
            {
                fail();
                failed = true;
                break;
            }
        }

        if(failed) continue;
    
        std::cout << "YES" << "\n";
        for(int x : path)
        {
            std::cout << x << " ";
        }

        std::cout << "\n";
        reset();
    }
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
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 80 + 5;
const int MAXM = 500 + 5;
const llong INF = 1e18 + 10;

int n, m;
bool isToll[MAXN];

struct Edge
{
    int idx;
    int from;
    int to;
    int w;
};

std::vector<Edge> edges;
llong prevDist[MAXN];
llong currDist[MAXN];
std::pair<int, int> par[2 * MAXM][MAXN];
int source, destination;

int bestStep;
llong ans;
std::vector<int> indexies;

void bellman_ford()
{
    std::fill(prevDist + 1, prevDist + n + 1, INF);
    std::fill(currDist + 1, currDist + n + 1, INF);
    prevDist[source] = 0;

    for(int step = 1 ; step <= 2 * m ; ++step)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            par[step][i] = {-1, -1};
        }
    }
    
    for(int step = 1 ; step <= 2 * m ; ++step)
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            currDist[i] = prevDist[i];
        }

        for(auto &[idx, from, to, w] : edges)
        {
            if(prevDist[from] == INF) continue;

            if(prevDist[from] + w < currDist[to])
            {
                currDist[to] = prevDist[from] + w;
                par[step][to] = {from, idx};

                if(to == destination)
                {
                    bestStep = step;
                }
            }
        }

        for(int i = 1 ; i <= n ; ++i)
        {
            prevDist[i] = currDist[i];
        }
    }

    ans = prevDist[destination];
}

void backtrack(int node, int step)
{
    if(step == 0)
    {
        return;
    }

    auto &[prev, idx] = par[step][node];
 
    if(prev == -1)
    {
        backtrack(node, step - 1);
    }

    indexies.push_back(idx);
    backtrack(prev, step - 1);
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)   
    {
        std::cin >> isToll[i];
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        edges.push_back({i, a, b, c});
    }

    source = 1, destination = n;
    bellman_ford();
    backtrack(n, bestStep);

    std::cout << ans << " " << indexies.size() << "\n";
    std::reverse(indexies.begin(), indexies.end());
    for(auto &i : indexies)
    {
        std::cout << i << " " << "1" << "\n";
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
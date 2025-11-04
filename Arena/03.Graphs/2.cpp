#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

const int MAXN = 5 * 1e5 + 10;
const int MAXM = 5 * 1e5 + 10;

int n, m;

struct Edge
{
    int to;
    int id;
};

std::vector<Edge> g[MAXN];
std::pair<int, int> edge[MAXM];
bool visited[MAXN];

bool bridge[MAXM];
int in[MAXN], low[MAXN];
int timer = 1;

int component[MAXN];
int reversed[MAXN]; 
int counter = 1;

std::vector<int> tree[MAXN];
std::vector<int> leaves;

void dfs1(int node, int parent)
{
    visited[node] = 1;
    in[node] = low[node] = timer++;

    bool skippedParent = false;
    for(auto &[to, id] : g[node])
    {   
        if(to == parent && !skippedParent)
        {
            skippedParent = 1;
            continue;
        }

        if(visited[to])
        {
            low[node] = std::min(low[node], in[to]);
        }
        else
        {
            dfs1(to, node);
            low[node] = std::min(low[node], low[to]);

            if(low[to] > in[node])
            {
                bridge[id] = 1;
            }
        }
    }
}

void dfs2(int node)
{
    visited[node] = 1;
    component[node] = counter;

    if(!reversed[counter])
    {
        reversed[counter] = node;
    }

    for(auto &[to, id] : g[node])
    {
        if(bridge[id])
        {
            continue;
        }

        if(!visited[to])
        {
            dfs2(to);
        }
    }
}

void dfs3(int node, int par)
{
    for(int &to : tree[node])
    {
        if(to == par)
        {
            continue;
        }

        dfs3(to, node);
    }

    if(tree[node].size() == 1)
    {
        leaves.push_back(node);
    }
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        edge[i] = {a, b};
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(!visited[i])
        {
            dfs1(i, -1);
        }
    }

    std::fill(visited + 1, visited + n + 1, false);
    
    for(int i = 1 ; i <= n ; ++i)
    {
        if(!visited[i])
        {
            dfs2(i);
            counter += 1;
        }
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        if(bridge[i])
        {
            int u = component[edge[i].first];
            int v = component[edge[i].second];
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
    }
    
    int root;
    for(int i = 1; i <= counter; ++i)
    {
        if(tree[i].size() >= 2)
        {
            root = i;
            break;
        }
    }

    dfs3(root, -1);

    int T = leaves.size();
    
    int H = (T + 1) / 2;
    std::cout << H << "\n";
    for(int i = 0 ; i < H ; ++i)
    {
        std::cout << reversed[leaves[i]] << " " << reversed[leaves[(i + H) % T]] << "\n";
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
    
    return 0;
}
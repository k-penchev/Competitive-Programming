#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

#define int long long

const int MAXN = 2000 + 10;
const int MAXM = 1e5 + 10;
const int MAXQ = 2001000 + 10;
const int B = 2 * 1e5;
const int MOD = 1e9 + 7;

int n, m, q;

struct Edge
{
    int from;
    int to;
};

std::vector<Edge> edges;

std::vector<int> g[MAXN], rev_g[MAXN];
std::vector<int> order;
bool vis[MAXN];
int component[MAXN][MAXM];

int answer[MAXQ];
int result = 0;

void dfs1(int node)
{
    vis[node] = 1;

    for(int to : g[node])
    {
        if(!vis[to])
        {
            dfs1(to);
        }
    }

    order.push_back(node);
}

void dfs2(int node, int comp_id, int edge_id, int banned_a, int banned_b)
{
    component[node][edge_id] = comp_id;

    for(int to : rev_g[node])
    {
        if((component[to][edge_id] == -1) && (node != banned_a || to != banned_b))
        {
            dfs2(to, edge_id, comp_id, banned_a, banned_b);
        }
    }
}

int mod_pow(int base, int exp, int mod) {
    int res = 1;
    base %= mod;

    while(exp > 0)
    {
        if(exp & 1) res = (1LL * res * base) % mod;
        
        base = (1LL * base * base) % mod;
        exp >>= 1;
    }

    return res;
}

void compute(int q_cnt)
{
    for(int i = 1 ; i <= q_cnt ; ++i)
    {
        result = (result + answer[i] * mod_pow(B, q_cnt - i, MOD)) % MOD;
        //std::cout << answer[i] << " ";
    }
    //std::cout << "\n";
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        edges.push_back({a, b});
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        if(!vis[i])
        {
            dfs1(i);
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j : g[i])
        {
            rev_g[j].push_back(i);
        }
    }

    int cnt = 1;
    
    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= m ; ++j)
        {
            component[i][j] = -1;
        }
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        for(int current : order)
        {
            if(component[current][i] == -1)
            {
                dfs2(current, cnt++, i, edges[i].to, edges[i].from);
            }
        }
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= m ; ++j)
        {
            std::cout << component[i][j] << " ";
        }
        std::cout << "\n";
    }
    
    /*std::cin >> q;

    if(q == 0)
    {
        int q_cnt = 0;
        for(int a = 1 ; a <= n ; ++a)
        {
            for(int b = a ; b <= n ; ++b)
            {
                if(component[a] != component[b])
                {
                    answer[++q_cnt] = 0;
                }
                else
                {
                    answer[++q_cnt] = m + 1;
                }
            }
        }

        compute(q_cnt);
    }
    else
    {
        for(int i = 1 ; i <= q ; ++i)
        {
            int a, b;
            std::cin >> a >> b;

            if(component[a] != component[b])
            {
                answer[i] = 0;
            }
            else
            {
                answer[i] = m + 1;
            }
        }

        compute(q);
    }


    std::cout << result << "\n";*/
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
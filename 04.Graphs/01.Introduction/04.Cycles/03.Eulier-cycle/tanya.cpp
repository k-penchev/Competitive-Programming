#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <stack>

const int MAXN = 2 * 1e5 + 10;
const int BIG_CONST = 1000;
const int MAX_NODES = 128 * BIG_CONST + 10;

int n;

struct Edge
{
    int to;
    int idx;
};

std::vector<Edge> graph[MAX_NODES];
int in[MAX_NODES], out[MAX_NODES];

bool visited[MAXN];
std::vector<int> path;
std::string answer;

void euler(int node)
{
    while(graph[node].size())
    {
        auto [to, idx] = graph[node].back();
        graph[node].pop_back();

        if(visited[idx])
        {
            continue;
        }

        visited[idx] = 1;
        euler(to);
    }

    path.push_back(node);
}

void die()
{
    std::cout << "NO" << "\n";
    exit(0);
}

void solve()
{
    std::cin >> n;

    int id = 0;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::string s;
        std::cin >> s;

        int u = s[0] * BIG_CONST + s[1];
        int v = s[1] * BIG_CONST + s[2];

        graph[u].push_back({v, id++});
        out[u]++; in[v]++;
    }

    int start = -1;
    int plus1 = 0, minus1 = 0;

    for(int i = 0; i < MAX_NODES; ++i)
    {
        int diff = out[i] - in[i];
        
        if(diff == 1)
        {
            plus1++;
            start = i;
        }
        else if(diff == -1)
        {
            minus1++;
        }
        else if(diff != 0)
        {
            die();
        }
    }

    if(!((plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0)))
    {
        die();
    }

    if(start == -1)
    {
        for(int i = 0; i < MAX_NODES; ++i)
        {
            if(out[i] > 0)
            {
                start = i;
                break;
            }
        }
    }

    euler(start);
    std::reverse(path.begin(), path.end());

    if(path.size() != n + 1)
    {
        die();
    }

    int first = path[0];
    answer.push_back(first / BIG_CONST);
    answer.push_back(first % BIG_CONST);

    for(int i = 1; i < path.size(); ++i)
    {
        int node = path[i];
        answer.push_back(node % BIG_CONST);
    }

    std::cout << "YES" << "\n";
    std::cout << answer << "\n";
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
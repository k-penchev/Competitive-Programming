#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

const int MAXN = 64 + 5;

struct Node
{
    int idx;
    int l, r;
    char type;
};

int n, m;
int counter;
int prefix[MAXN][MAXN];
int table[MAXN][MAXN];
std::vector<Node> nodes;

int createNode(int l, int r, char type)
{
    counter += 1;   
    nodes.push_back({counter, l, r, type});
    return counter;
}

int getTableID(int row, int col)
{
    return (row - 1) * m + col;
}

void divideRow(int row, int l, int r)
{
    if(l == r)
    {
        prefix[row][l] = getTableID(row, l);
        return;
    }

    int mid = l + r >> 1;
    divideRow(row, l, mid); divideRow(row, mid + 1, r);

    for(int i = mid + 1 ; i <= r ; ++i)
    {
        prefix[row][i] = createNode(prefix[row][mid], prefix[row][i], '+');
    }
}

void divideCol(int col, int l, int r)
{
    if(l == r)
    {
        table[l][col] = prefix[l][col];
        return;
    }

    int mid = l + r >> 1;
    divideCol(col, l, mid); divideCol(col, mid + 1, r);

    for(int i = mid + 1 ; i <= r ; ++i)
    {
        table[i][col] = createNode(table[mid][col], table[i][col], '+');
    }
}

void solve()
{
    counter = n * m;

    for(int i = 1 ; i <= n ; ++i)
    {
        divideRow(i, 1, m);
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        divideCol(i, 1, n);
    }
}

void output()
{
    std::cout << counter << "\n";

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= m ; ++j)
        {
            std::cout << table[i][j] << " "; 
        }   

        std::cout << "\n";
    }

    for(auto [idx, l, r, type] : nodes)
    {
        std::cout << idx << " = " << l << " " << type << " " << r << "\n";
    }
}

void input()
{
    std::cin >> n >> m;
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
    input();
    solve();
    output();

    return 0;
}
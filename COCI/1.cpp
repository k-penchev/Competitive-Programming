#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

const int MAXN = 500 + 5;

int n, m, k;
std::vector<std::string> line[MAXN];
int a, b, c;

bool compare(std::string a, std::string b)
{
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());

    for(int i = 0 ; i < k ; ++i)
    {
        if(a[i] != b[i]) return false;
    }

    return true;
}

void compute()
{
    for(int i = 1 ; i <= n ; i += 4) //stanza
    {
        bool flag = 1;
        for(int j = i ; j <= i + 3 && flag ; ++j)
        {
            if(line[j].back().size() < k) flag = 0;
        }

        if(!flag) continue;

        //a
        if(compare(line[i].back(), line[i + 1].back()) &&
            compare(line[i + 2].back(), line[i + 3].back())) 
        {
            a += 1;
        }

        //b
        if(compare(line[i].back(), line[i + 2].back()) &&
            compare(line[i + 1].back(), line[i + 3].back())) 
        {
            b += 1;
        }

        //c
        if(compare(line[i].back(), line[i + 3].back()) &&
            compare(line[i + 1].back(), line[i + 2].back())) 
        {
            c += 1;
        }
    }
}

void solve()
{
    std::cin >> n >> m >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::string s;
        for(int j = 1 ; j <= m ; ++j)
        {
            std::cin >> s;
            line[i].push_back(s);
        }
    }

    compute();

    std::cout << a << " " << b << " " << c << "\n";
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
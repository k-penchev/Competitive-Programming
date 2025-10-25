#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>

const int MAXN = 2e5 + 10;
const int MOD1 = 100000000;
const int MOD2 = 998244353;

int n, m;
int a[MAXN], toCompress[MAXN];
std::unordered_map<int, int> compressed;
int globalNum = 0;
int lastOutput = 0;

int cnt[MAXN];

void clear(int l, int r)
{
    for(int i = l ; i <= r ; ++i)
    {
        cnt[compressed[a[i]]] = 0; 
    }
}

void divide(int l, int r)
{
    if(l > r) return;

    if(l == r)
    {
        lastOutput = (lastOutput + compressed[a[l]]) % MOD2;
    }

    int m = (l + r) / 2;
    divide(l, m); divide(m + 1, r);

    std::set<int> major;

    clear(l, m);
    for(int i = m ; i >= l ; --i)
    {
        cnt[compressed[a[i]]] += 1;

        if(cnt[compressed[a[i]]] > (m - i + 1) / 2)
        {
            major.insert(compressed[a[i]]);
        }
    }

    clear(m + 1, r);
    for(int i = m + 1 ; i <= r ; ++i)
    {
        cnt[compressed[a[i]]] += 1;

        if(cnt[compressed[a[i]]] > (i - (m + 1) + 1) / 2)
        {
            major.insert(compressed[a[i]]);
        }
    }

    for(auto it = major.begin() ; it != major.end(); ++it)
    {
        for(int i = m ; i >= l ; --i)
        {
            if(compressed[a[i]] == *it)
            {
                
            }
        }
    }
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        toCompress[i] = a[i];
    }

    std::sort(toCompress + 1, toCompress + n + 1);

    for(int i = 1 ; i <= n ; ++i)
    {
        compressed[toCompress[i]] = globalNum;

        if(i + 1 <= n && toCompress[i] != toCompress[i + 1])
        {
            globalNum += 1;
        }
    }

    std::cin >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int l, r, t;
        std::cin >> l >> r >> t;

        int type, p, q;
       
        type = ((t + lastOutput) % 2) + 1;
        if(type == 1)
        {
            p = ((l + lastOutput) % n) + 1;
            q = ((r + lastOutput) % MOD1) + 1;

            a[p] = q;

            if(!compressed[q])
            {
                compressed[q] = ++globalNum;
            }
        }
        else
        {
            p = ((l + lastOutput) % MOD1) + 1;
            q = ((r + lastOutput) % n) + 1;

            lastOutput = 0;
            divide(p, q);
            std::cout << lastOutput << "\n";
        }   
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
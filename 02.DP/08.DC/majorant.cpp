#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>

#define int long long

const int MAXN = 65000 + 10;
const int MOD1 = 100000000;
const int MOD2 = 998244353;

int n, m;
int a[MAXN], toCompress[MAXN];
std::unordered_map<int, int> compressed, rev;
int globalNum = 1;
int lastOutput = 0, ans = 0;

std::set<int> major;
int cnt[5 * MAXN], suffix[2 * MAXN + 10];

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

    std::cout << "\n";

    std::cout << l << " " << r << "\n";

    if(l == r)
    {
        ans = (ans + a[l]) % MOD2;
        return;
    }

    int m = (l + r) / 2;
    divide(l, m); divide(m + 1, r);

    major.clear();

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
        int currentMajor = *it;

        for(int i = n - (r - l + 1) ; i <= n + (r - l + 1) + 1 ; ++i)
        {
            suffix[i] = 0;
        }

        int count = 0;
        for(int i = m ; i >= l ; ++i)
        {
            if(compressed[a[i]] == currentMajor)
            {
                count += 1;
            }
            else
            {
                count -= 1;
            }

            suffix[count + n] += 1;
        }

        for(int i = n + (r - l + 1) ; i >= n - (r - l + 1) ; --i)
        {
            suffix[i] += suffix[i + 1];
        }

        count = 0;
        for(int i = m + 1 ; i <= r ; ++i)
        {
            if(compressed[a[i]] == currentMajor)
            {
                count += 1;
            }
            else
            {
                count -= 1;
            }

            ans = (ans + rev[currentMajor] * suffix[-count + n + 1]) % MOD2;
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
        rev[globalNum] = toCompress[i];

        if(i + 1 <= n && toCompress[i] != toCompress[i + 1])
        {
            globalNum += 1;
        }
    }

    std::cin >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int ql, qr, qt;
        std::cin >> ql >> qr >> qt;

        int type, p, q;
       
        type = ((qt + lastOutput) % 2) + 1;
        if(type == 1)
        {
            p = ((ql + lastOutput) % n) + 1;
            q = ((qr + lastOutput) % MOD1) + 1;

            a[p] = q;

            if(compressed[q] == 0)
            {
                compressed[q] = ++globalNum;
                rev[globalNum] = q;          
            }
        }
        else
        {
            p = ((ql + lastOutput) % n) + 1;
            q = ((qr + lastOutput) % n) + 1;

            divide(p, q);
            std::cout << ans << "\n";

            lastOutput = ans;
            ans = 0;
        }   
    }
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}
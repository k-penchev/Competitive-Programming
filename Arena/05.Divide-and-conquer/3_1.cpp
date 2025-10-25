#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 1e5 + 10;
const int INF = 1e9 + 10;

int n;
int query[MAXN], idx[MAXN], rem[MAXN];
int ans = 0;

struct Element
{
    int value;
    int time;
};

struct Fenwick
{
    int bit[MAXN];

    void set()
    {
        std::fill(bit + 1, bit + n + 1, 0);
    }

    void update(int idx, int val)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] += val;
        }
    }

    int query(int idx)
    {
        int s = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            s += bit[idx];
        }

        return s;
    }

    int querySmaller(int idx)
    {
        return query(idx - 1);
    }

    int queryBigger(int idx)
    {
        return query(n) - query(idx);
    }
};


Element element[MAXN];
Fenwick invFenwick;
Fenwick left, right;

void divide(int l, int r)
{
    if(l == r) return;

    int m = (l + r) / 2;
    divide(l, m); divide(m + 1, r);

    std::vector<std::pair<Element, bool>> currentElements;
    currentElements.reserve(r - l + 1);

    for(int i = l ; i <= m ; ++i)
    {
        currentElements.push_back({element[i], 0});
    }

    for(int i = m + 1 ; i <= r ; ++i)
    {
        currentElements.push_back({element[i], 1});
    }

    std::sort(currentElements.begin(), currentElements.end(), [&](const std::pair<Element, bool>& a, const std::pair<Element, bool>& b)
    {
        return a.first.time > b.first.time;
    });

    for(auto& [currentElement, side] : currentElements)
    {
        if(side == 0)
        {
            left.update(currentElement.value, +1); 
            rem[currentElement.value] += right.querySmaller(currentElement.value);
        }
        else
        {
            right.update(currentElement.value, +1); 
            rem[currentElement.value] += left.queryBigger(currentElement.value);
        }
    }

    for(auto& [currentElement, side] : currentElements)
    {
        if(side == 0)
        {
            left.update(currentElement.value, -1); 
        }
        else
        {
            right.update(currentElement.value, -1); 
        }
    }
} 

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> element[i].value;
        idx[element[i].value] = i;
        element[i].time = INF;
    }

    for(int i = 1 ; i <= n - 2 ; ++i)
    {
        std::cin >> query[i];
        element[idx[query[i]]].time = i;
    }

    invFenwick.set();
    for(int i = n ; i >= 1 ; --i)
    {
        ans += invFenwick.query(element[i].value - 1);
        invFenwick.update(element[i].value, +1);
    }

    divide(1, n);

    std::cout << ans << " ";

    for(int i = 1 ; i <= n - 2 ; ++i)
    {
        ans -= rem[query[i]];
        std::cout << ans << " ";
    }

    std::cout << "\n";
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
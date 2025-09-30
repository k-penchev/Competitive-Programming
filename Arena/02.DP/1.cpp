#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 80;

int n, k;

struct Person
{
    int w;
    int t;
};

Person p[MAXN];

void solve()
{
    std::cin >> n >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> p[i].w >> p[i].t;
    }

    std::sort(p + 1, p + n + 1, [&](const Person& a, const Person& b)
    {
        int f = std::max(a.w, b.w + a.t);
        int s = std::max(b.w, a.w + b.t);

        return f < s;
    });

    int total = 0, best = 0;
    for(int i = 1 ; i <= n ; ++i)
    {
        int current = total + p[i].w;
        best = std::max(best, current);

        total += p[i].t;
    }

    std::cout << best << "\n";
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
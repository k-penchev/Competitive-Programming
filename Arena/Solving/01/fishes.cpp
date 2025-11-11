#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int MAX_FEN = 2 * MAXN + 10;

int n, m;

struct Fenwick
{
    int bit[MAX_FEN];
    int max;

    void set()
    {
        std::fill(bit + 1, bit + max + 1, 0);
    }

    void update(int idx, int val)
    {
        for(; idx <= max ; idx += (idx & (-idx)))
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
};

struct Fish
{
    int x;
    int y;

    int left()
    {
        return y + x;
    }

    int right()
    {
        return y - x;
    }
};

struct Fisherman
{
    int idx;
    int a;
    int l;

    int left()
    {
        return l + a;
    }

    int right()
    {
        return l - a;
    }
};

Fenwick active;
Fish fish[MAXN];
Fisherman fisherman[MAXN];

std::vector<int> toCompress;
std::unordered_map<int, int> map;

int answer[MAXN];

void compress()
{
    for(int i = 1 ; i <= m ; ++i)
    {
        toCompress.push_back(fish[i].right());
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        toCompress.push_back(fisherman[i].right());
    }

    std::sort(toCompress.begin(), toCompress.end());

    int cnt = 1;
    for(int i = 0 ; i < toCompress.size() ; ++i)
    {
        map[toCompress[i]] = cnt;

        if(i != toCompress.size() - 1)
        {
            if(toCompress[i] != toCompress[i + 1])
            {
                cnt += 1;
            }
        }
    }

    active.max = cnt;
}

void solve()
{
    compress();

    std::sort(fish + 1, fish + m + 1, [&](Fish &a, Fish &b)
    {
        return a.left() < b.left();
    });

    std::sort(fisherman + 1, fisherman + n + 1, [&](Fisherman &a, Fisherman &b)
    {
        return a.left() < b.left();
    });

    int ptr = 1;
    active.set();
    for(int i = 1 ; i <= n ; ++i)
    {
        while(ptr <= m && fish[ptr].left() <= fisherman[i].left())
        {
            active.update(map[fish[ptr].right()], +1);
            ptr += 1;
        }

        answer[fisherman[i].idx] += active.query(map[fisherman[i].right()]);
    }
}

void output()
{
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cout << answer[i] << " ";
    }

    std::cout << "\n";
}

void input()
{
    std::cin >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        std::cin >> fish[i].x;
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        std::cin >> fish[i].y;
    }

    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        fisherman[i].idx = i;
        std::cin >> fisherman[i].a;
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> fisherman[i].l;
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
    input();
    solve();
    output();
    
    return 0;
}
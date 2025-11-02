#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int BUCKET_COUNT = 320 + 5;

int n, m, q;
long long a[MAXN];
std::vector<int> set[MAXN];
std::vector<int> heavySets;

bool heavy[MAXN];
int idxHeavy[MAXN];
int inBucket[BUCKET_COUNT][MAXN];
int intersectCnt[BUCKET_COUNT][MAXN];
long long sumHeavy[BUCKET_COUNT], lazyHeavy[MAXN];

int counter = 0;

int getID(int x)
{
    return idxHeavy[x];
}

int intersection(int x, int y) 
{
    int res = 0;

    for(int i = 1 ; i < set[y].size() ; ++i)
    {
        if(inBucket[getID(x)][set[y][i]])
        {
            res += 1;
        }
    } 

    return res;
}

void calculate(int idx)
{
    for(int i = 1 ; i <= m ; ++i)
    {
        intersectCnt[getID(idx)][i] = intersection(idx, i);
    }
}

void precompute(int idx)
{
    for(int i = 1 ; i < set[idx].size() ; ++i)
    {
        inBucket[getID(idx)][set[idx][i]] = 1;
        sumHeavy[getID(idx)] += a[set[idx][i]];
    }
}

void solve()
{
    std::cin >> n >> m >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int size;
        std::cin >> size;
        set[i].resize(size + 1);
        
        for(int j = 1 ; j <= size ; ++j)
        {
            std::cin >> set[i][j];
        }

        if(size >= BUCKET_COUNT)
        {
            heavy[i] = 1;
            heavySets.push_back(i);
            idxHeavy[i] = ++counter;
            precompute(i);
        }
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        if(heavy[i])
        {
            calculate(i);
        }
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        char type;
        long long x, k;
        std::cin >> type >> x;

        if(type == '?')
        {
            long long answer = 0;

            if(!heavy[x])
            {
                for(int j = 1 ; j < set[x].size() ; ++j)
                {
                    answer += a[set[x][j]];
                }

                for(int h : heavySets)
                {
                    answer += 1LL * lazyHeavy[getID(h)] * intersectCnt[getID(h)][x];
                }
            }
            else
            {
                answer += sumHeavy[getID(x)];

                for(int h : heavySets)
                {
                    answer += 1LL * lazyHeavy[getID(h)] * intersectCnt[getID(h)][x];
                }
            }

            std::cout << answer << "\n";
        }
        else
        {
            std::cin >> k;

            if(!heavy[x])
            {
                for(int j = 1 ; j < set[x].size() ; ++j)
                {
                    a[set[x][j]] += k;
                }

                for(int h : heavySets)
                {
                    sumHeavy[getID(h)] += 1LL * intersectCnt[getID(h)][x] * k;
                }
            }
            else
            {
                lazyHeavy[getID(x)] += k;
            }
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
    
    return 0;
}
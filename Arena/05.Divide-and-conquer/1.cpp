#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 128 + 10; 
const int BIG_CONST = 1000; 

int n;
int a[MAXN], b[MAXN];
std::vector<int> positions;

void swap(int idxL, int idxR)
{
    positions.push_back(idxR);

    int temp = a[idxR];

    for(int i = idxR ; i > idxL ; --i)
    {
        a[i] = a[i - 1];
    }

    a[idxL] = temp;
}

int getPivot(int l, int r)
{
    for(int i = l ; i <= r ; ++i)
    {
        b[i] = a[i];
    }

    std::sort(b + l, b + r + 1);
    return b[l + ((r - l + 1) / 2) - 1]; 
}

int getID(int val, int pivot)
{
    return (val <= pivot ? 1 : 2);
}

void calcAns(int len)
{
    
    int half = len / 2;
    int pivot = getPivot(1, len);

    int cnt = 0;
    for(int i = 1 ; i <= half ; ++i)
    {
        cnt += (getID(a[i], pivot) == 2);
    }

    while(cnt > 0)
    {
        if(getID(a[half], pivot) == 1)
        {
            swap(1, half);
        }
        else
        {
            swap(1, len);

            cnt -= 1;
            if(getID(a[1], pivot) == 2) cnt += 1;
        }
    }
}

void divide(int len)
{
    if(len <= 1)
    {
        return;
    }

    calcAns(len);

    int half = len / 2;

    divide(half);
    for(int i = 0 ; i < half ; ++i) swap(1, len);

    divide(half);
    for(int i = 0 ; i < half ; ++i) swap(1, len);
}

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        a[i] = BIG_CONST * a[i] + i;
    }

    divide(n);

    std::cout << positions.size() << "\n";

    for(std::size_t i = 0 ; i < positions.size() ; ++i)
    {
        std::cout << positions[i] << (i + 1 == positions.size() ? '\n' : ' ');
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

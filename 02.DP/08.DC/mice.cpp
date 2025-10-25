#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXK = 19;
const int MAXN = (1 << MAXK) + 10;

int k;
int a[MAXN];
int ans = 0;

void copyElements(int * result, std::vector<int>& left, std::vector<int>& right)
{
    for(int i = 0 ; i < left.size(); ++i)
    {
        result[i] = left[i];
    }

    for(int i = 0 ; i < right.size(); ++i)
    {
        result[left.size() + i] = right[i];
    }
}

int countInversions(std::vector<int>& left, std::vector<int>& right)
{
    int inversions = 0;
    int l_ptr = 0, r_ptr = 0;

    int l_size = left.size(), r_size = right.size();

    for(int i = 0 ; i < l_size + r_size ; ++i)
    {
        if(l_ptr == l_size)
        {
            r_ptr += 1;
            continue;
        }

        if(r_ptr == r_size)
        {
            l_ptr += 1;
            continue;
        }

        if(left[l_ptr] <= right[r_ptr])
        {
            l_ptr += 1;
        }
        else
        {
            r_ptr += 1;
            inversions += (l_size - l_ptr);
        }
    }

    return inversions;
}

void merge(int l, int m, int r)
{
    int l_size = m - l + 1;
    int r_size = r - m;

    std::vector<int> left(l_size, 0);
    std::vector<int> right(r_size, 0);

    for(int i = 0 ; i < l_size ; ++i)
    {
        left[i] = a[l + i];
    }

    for(int i = 0 ; i < r_size ; ++i)
    {
        right[i] = a[m + 1 + i];
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int first = countInversions(left, right);
    int second = countInversions(right,left);

    ans += std::min(first, second);

    if(first <= second) copyElements(a + l, left, right);
    else copyElements(a + l, right, left);
}

void solve(int l, int r)
{
    if(l == r) return;

    int m = (l + r) / 2;

    solve(l, m);
    solve(m + 1, r);

    merge(l, m, r);
}

void solve()
{
    std::cin >> k;

    for(int i = 1 ; i <= (1 << k) ; ++i)
    {
        std::cin >> a[i];
    }

    solve(1, (1 << k));

    std::cout << ans << "\n";
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
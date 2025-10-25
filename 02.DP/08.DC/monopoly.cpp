#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 5 * 1e5 + 10;

int n, m;
int a[MAXN];
int best_len, best_idx;

void check(int l, int r)
{
    if(r - l + 1 > best_len)
    {
        best_len = r - l + 1;
        best_idx = l;
    } 
    else if(r - l + 1 == best_len)
    {
        best_idx = std::min(best_idx, l);
    }
}

void merge(int l, int mid, int r)
{
    int left_len = mid - l + 1;
    int right_len = r - mid;

    std::vector<int> left_suffix(left_len, 0);
    std::vector<int> min_suffix(left_len, 0);
    std::vector<int> right_prefix(right_len, 0);

    left_suffix[left_len - 1] = a[mid];
    for(int i = left_len - 2 ; i >= 0 ; --i)
    {
        left_suffix[i] = left_suffix[i + 1] + a[l + i];
    }

    right_prefix[0] = a[mid + 1];
    for(int i = 1 ; i < right_len ; ++i)
    {
        right_prefix[i] = right_prefix[i - 1] + a[mid + 1 + i];
    }

    min_suffix[0] = left_suffix[0];
    for(int i = 1 ; i < left_suffix.size() ; ++i)
    {
        min_suffix[i] = std::min(min_suffix[i - 1], left_suffix[i]);
    }

    for(int i = 0 ; i < right_prefix.size() ; ++i)
    {
        int current = right_prefix[i];

        int l_ptr = -1, r_ptr = min_suffix.size(), binary_mid = (l_ptr + r_ptr) / 2;

        while(l_ptr + 1 < r_ptr)
        {
            int binary_mid = (l_ptr + r_ptr) / 2;

            if(min_suffix[binary_mid] <= m - current)
            {
                r_ptr = binary_mid;
            }
            else
            {
                l_ptr = binary_mid;
            }
        }

        int diff = min_suffix.size() - r_ptr;
        check(mid - diff + 1, mid + 1 + i);
    }
}

void calc(int l, int r)
{
    if(l == r) 
    {
        if(a[l] <= m)
        {
            check(l, l);
        }
        
        return;
    }

    int mid = (l + r) / 2;

    calc(l, mid);
    calc(mid + 1, r);

    merge(l, mid, r);
}

void solve()
{
    std::cin >> n >> m;

    for(int i = 0 ; i < n ; ++i)
    {
        std::cin >> a[i];
    }

    calc(0, n - 1);
    
    std::cout << best_len << " " << best_idx + 1 << "\n";
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
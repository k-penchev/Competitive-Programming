#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 1;

int n, m, k;

vector<int> _log;

void build_common_log_table()
{
    _log.resize(n + 1);

    _log[1] = 0;

    for(int i = 2 ; i <= n ; ++i)
    {
        _log[i] = _log[i / 2] + 1;
    }
}

struct Sparse
{
    vector<vector<int>> sparse;
    vector<int> _log;

    void build(vector<int>& v)
    {
        int rows_size = n;
        int cols_size = log2(n) + 1;
    
        sparse.resize(rows_size, vector<int>(cols_size));
        
        for(int i = 0 ; i < n ; ++i)
        {
            sparse[i][0] = v[i];
        }

        for(int j = 1 ; (1 << j) <= n ; ++j)
        {
            for(int i = 0 ; i + (1 << j) - 1 < n ; ++i)
            {
                sparse[i][j] = max(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r, vector<int>& lg)
    {
        int k = lg[r - l + 1];
        return max(sparse[l][k], sparse[r - (1 << k) + 1][k]);
    }
};

Sparse tables[5];
vector<vector<int>> values;

bool check(int window_size, vector<int>& out)
{
    if(window_size == 0)
    {
        out.assign(m, 0);
        return true;
    }

    vector<int> res(m, 0);

    for(int s = 0, e = window_size - 1 ; e < n ; ++s, ++e)
    {
        long long sum = 0;

        for(int j = 0 ; j < m ; ++j)
        {
            res[j] = tables[j].query(s, e, _log);
            sum += res[j];

            if(sum > k) break;
        }

        if(sum <= k)
        {
            out = res;
            return true;
        }
    }

    return false;
}

void calculate_max_shots()
{
    vector<int> best(m, 0), tmp;

    int lPtr = 0, rPtr = n;

    while(lPtr <= rPtr)
    {
        int mid = (lPtr + rPtr) / 2;

        if(check(mid, tmp))
        {
            best = tmp;
            lPtr = mid + 1;
        }
        else
        {
            rPtr = mid - 1;
        }
    }


    for(int i = 0 ; i < m ; ++i)
    {
        cout << best[i] << " ";
    }

    cout << "\n";
}

void solve()
{
    cin >> n >> m >> k;

    values.resize(m, vector<int>(n));

    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < m ; ++j)
        {
            cin >> values[j][i];
        }
    }

    build_common_log_table();

    int idx = 0;

    for(auto& v : values)
    {
        tables[idx].build(v);
        idx++;
        v.clear();
    }

    calculate_max_shots();
}

void fastIO()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}
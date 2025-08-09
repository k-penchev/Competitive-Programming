#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
const int INF = 1e9 + 10;

int n, k;
vector<int> v;
int arr[MAXN];
vector<pair<int, int>> monotone;

int binary(int x)
{
    int lPtr = -1, rPtr = monotone.size() + 1;

    while(rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(monotone[mid].first > x)
        {
            lPtr = mid;
        }
        else
        {
            rPtr = mid;
        }
    }

    return lPtr;
}

long long count_pairs()
{
    long long pairs = 0;

    monotone.push_back({INF, 0});

    for(int i = 1 ; i <= n ; ++i)
    {
        cout << "\n";

        while(monotone.back().first < arr[i])
        {
            monotone.pop_back();
        }

        monotone.push_back({arr[i], i});


        for(int k = 0 ; k < monotone.size(); ++k)
        {
            cout << "(" << monotone[k].first << "," << monotone[k].second << ")" << " ";
        }

        cout << "\n";

        pairs += monotone.size() - 2;

        cout << "+" << monotone.size() - 1 << "\n";

        int ptr = binary(arr[i]);

        int from = monotone[ptr].second + 1;
        int to = monotone.back().second;
        int total_elements = to - from + 1;
        
        pairs += (to - from + 1) - (monotone.size() - ptr + 1);

        cout << "++" << (to - from + 1) - (monotone.size() - ptr + 1) << "\n";

        cout << "\n";
    }

    return pairs;
}

/*
long long init(std::vector<int> h, int K)
{
    n = h.size();
    k = K;

    for(int i = 1 ; i <= h.size() ; ++i)
    {
        arr[i] = h[i - 1];
    }
    
    return count_pairs();
}*/


void solve()
{
    cin >> n >> k ;

    for(int i = 0 ; i < n ; ++i)
    {
        int x; cin >> x;
        v.push_back(x);
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        arr[i] = v[i - 1];
    }

    cout << count_pairs() << "\n"; 
}   

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}



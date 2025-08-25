//Dynamic programming
#include <bits/stdc++.h>

using namespace std;

const int MAXK = 20;
const int MAXN = 100;

const int INF = 1e9;

int K, N;
int total[(1 << MAXK)][MAXN];
int price[MAXK][MAXN];

void solve()
{
    cin >> K >> N;

    for(int product = 0 ; product < K ; ++product)
    {
        for(int day = 0 ; day < N ; ++day)
        {
            cin >> price[product][day];
        }
    }

    int FULL = (1 << K) - 1; 

    
    for (int set = 0; set <= FULL; ++set) total[set][0] = INF; 
    
    total[0][0] = 0;                                           
    
    for(int product = 0 ; product < K ; ++product)
    {
        int set = (1 << product);
        total[set][0] = min(total[set][0], price[product][0]); // buy exactly one on day 0
    }

    
    for(int day = 1 ; day < N ; ++day)
    {
        for(int set = 0 ; set <= FULL ; ++set)
        {
            total[set][day] = total[set][day - 1]; // do not buy anything

            for(int product = 0 ; product < K ; ++product)
            {
                if(set & (1 << product)) // is the product in the set
                {
                    total[set][day] = min(
                        total[set][day], // best so far
                        total[set ^ (1 << product)][day - 1] + price[product][day] // buy the current product
                    );
                }
            }
        }
    }

    cout << total[FULL][N - 1] << "\n"; 
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}

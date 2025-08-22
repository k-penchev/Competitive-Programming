#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e3 + 10;
const ll INF = 1e18;

int T, N, M, W;
int x, y;

void solve()
{
    cin >> T;

    for(int rep = 0 ; rep < T ; ++rep)
    {
        cin >> N >> M;

        vector<pair<int, int>> left, right;

        ll leftSum = 0, rightSum = 0;

        for(int i = 0 ; i < N ; ++i)
        {
            cin >> x >> y;
            left.push_back({x, y});
            leftSum += x;
        }

        for(int i = 0 ; i < M ; ++i)
        {
            cin >> x >> y;
            right.push_back({x, y});
            rightSum += x;
        }

        W = min(leftSum, rightSum);

        vector<ll> dpLeft(W + 1, -INF), dpRight(W + 1, -INF);

        dpLeft[0] = dpRight[0] = 0;

        for(auto& it : left)
        {
            for(int j = W ; j >= it.first ; --j)
            {
                dpLeft[j] = max(dpLeft[j], dpLeft[j - it.first] + it.second);
            }
        }

        for(auto& it : right)
        {
            for(int j = W ; j >= it.first ; --j)
            {
                dpRight[j] = max(dpRight[j], dpRight[j - it.first] + it.second);
            }
        }

        ll best_result = -INF;

        for(int i = 0 ; i <= W ; ++i)
        {
            if(dpLeft[i] != -INF && dpRight[i] != -INF)
            {
                best_result = max(best_result, dpLeft[i] + dpRight[i]);
            }
        }

        cout << (best_result == -INF ? 0 : best_result ) << "\n";
    }
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
#include "grid.h"
#include <bits/stdc++.h>

const long long INF = 1e18;

long long max_profit(int N, int M, int C, std::vector<std::vector<int>> A)
{
    long long dp[N + 1][M + 1];

    for(int i = 0 ; i < N ; ++i)
    {
        for(int j = 0 ; j < M ; ++j)
        {
            dp[i][j] = -INF;
        }
    }

    dp[0][0] = 0;

    for(int i = 0 ; i < N ; ++i)
    {
        for(int j = 0 ; j < M ; ++j)
        {
            if (dp[i][j] == -INF) continue;

            for(int d = 1 ; i + d < N ; ++d)
            {
                long long w = llabs(A[i][j] - A[i + d][j]) - C;   
                dp[i + d][j] = std::max(dp[i + d][j], dp[i][j] + w);
            }

            for(int d = 1 ; j + d < M ; ++d)
            {
                long long w = llabs(A[i][j] - A[i][j + d]) - C;   
                dp[i][j + d] = std::max(dp[i][j + d], dp[i][j] + w);
            }
        }
    }

    return dp[N - 1][M - 1];
}

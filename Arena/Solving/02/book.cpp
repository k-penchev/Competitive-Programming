#include <bits/stdc++.h>

using namespace std;

const int MAXM = 1e3 + 5;

int n, m;

struct Book
{
    int pages;
    double amout;
};

vector<Book> books;

double dp[MAXM];

void solve()
{
    cin >> n >> m;

    books.resize(n + 1);

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> books[i].pages >> books[i].amout;
    }

    for(auto book : books)
    {
        for(int j = m ; j >= book.pages ; --j)
        {
            dp[j] = max(dp[j], dp[j - book.pages] + book.amout);
        }
    }

    cout << fixed << setprecision(2) << dp[m] << "\n";
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
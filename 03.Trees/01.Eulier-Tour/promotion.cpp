#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n;
pair<int, int> toCompress[MAXN];
int val[MAXN];
vector<vector<int>> tree(MAXN);

struct MergeSortTree
{
    struct Node
    {
        vector<int> v;

        Node(){}
    };

    Node seg[4 * MAXN];

    Node combine(const Node& left, const Node& right)
    {
        if (left.v.empty())  return right;
        if (right.v.empty()) return left;

        Node res;

        res.v.reserve(left.v.size() + right.v.size());

        int lPtr = 0, rPtr = 0;
        
        for(int i = 1 ; i <= left.v.size() + right.v.size() ; ++i)
        {
            if(lPtr == left.v.size())
            {
                res.v.push_back(right.v[rPtr++]);
                continue;
            }

            if(rPtr == right.v.size())
            {
                res.v.push_back(left.v[lPtr++]);
                continue;
            }

            if(left.v[lPtr] < right.v[rPtr])
            {
                res.v.push_back(left.v[lPtr++]);
            }
            else
            {
                res.v.push_back(right.v[rPtr++]);
            }
        }

        return res;
    }

    void build(int idx, int low, int high, vector<int>& arr)
    {
        if(low == high)
        {
            seg[idx].v.push_back(arr[low]);
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid, arr);
        build(right, mid + 1, high, arr);

        seg[idx] = combine(seg[left], seg[right]);
    }

    int binary(vector<int>& vals, int k)
    {
        int l = -1, r = vals.size();

        while(r > l + 1)
        {
            int m = (l + r) / 2;

            if(vals[m] > k) r = m;
            else l = m;
        }

        return vals.size() - r;
    }

    int query(int idx, int low, int high, int queryL, int queryR, int k)
    {
        if(queryL > high || queryR < low)
        {
            return 0;
        }
        else if(queryL <= low && high <= queryR)
        {
            return binary(seg[idx].v, k);
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        int le, ri;

        le = query(left, low, mid, queryL, queryR, k);
        ri = query(right, mid + 1, high, queryL, queryR, k);

        return le + ri;
    }
};

MergeSortTree seg;
int in[MAXN], out[MAXN], timer = 0;

void euler(int node, int par)
{
    in[node] = ++timer;

    for(int& to : tree[node])
    {
        if(to == par) continue;
        euler(to, node);
    }

    out[node] = timer;
}

void solve()
{
    euler(1, 0);

    vector<int> flat(n + 1);

    for(int i = 1 ; i <= n ; ++i)
    {
        flat[in[i]] = val[i];
    }

    seg.build(1, 1, n, flat);

    for(int i = 1 ; i <= n ; ++i)
    {
        cout << seg.query(1, 1, n, in[i], out[i], val[i]) << "\n";
    }
}

void input()
{

    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        int x; cin >> x;
        toCompress[i] = {x, i};
    }

    sort(toCompress + 1, toCompress + n + 1);

    int cnt = 1;

    for(int i = 1 ; i <= n ; ++i)
    {
        val[toCompress[i].second] = cnt;
        if(i + 1 <= n && toCompress[i].first != toCompress[i + 1].first) cnt++;
    }

    for(int i = 2 ; i <= n ; ++i)
    {
        int par; cin >> par;

        tree[par].push_back(i);
        tree[i].push_back(par);
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
    input();
    solve();
    
    return 0;
}
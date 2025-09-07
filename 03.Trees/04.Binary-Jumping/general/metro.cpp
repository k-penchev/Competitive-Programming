/*
    * The idea is that we only need to know the minimum (minSum) and maximum (maxSum) 
    * subsegment of the path from A to B. It can be proved that it is enough to check 
    * whether "k" is in the interval [minSum ; maxSum]. If so, the answer to the query is 
    * "Yes", otherwise "No". 

    * Thus the problem is reduced to handle two types of queries :
        * 1) Add new node to the tree and precompute its values
        * 2) Combine the results from the paths (A --> LCA) and (B --> LCA)
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;
const int MAXLOG = 17 + 1;

int T, N;

struct Path
{
    int sum;        

    int maxSum;     
    int minSum;     

    int maxPrefix;  
    int minPrefix;  
    
    int maxSuffix;
    int minSuffix;  

    Path()
    {                
        sum = 0;
        maxSum = minSum = 0;
        maxPrefix = minPrefix = 0;
        maxSuffix = minSuffix = 0;
    }

    Path(int value)
    {
        sum = value;
        maxSum    = max(0, value);
        minSum    = min(0, value);
        maxPrefix = max(0, value);
        minPrefix = min(0, value);
        maxSuffix = max(0, value);
        minSuffix = min(0, value);
    }
};

int liftNode[MAXN][MAXLOG]; // standard binary lifting
Path liftPath[MAXN][MAXLOG]; // liftPath[i][j] represent Path from i to 2 ^ j (exclusive)
int val[MAXN]; // value of each node 
int depth[MAXN]; // depth of each node 
int cntNodes;

Path reversePath(const Path& P)
{
    Path R = P;
   
    swap(R.maxPrefix, R.maxSuffix);
    swap(R.minPrefix, R.minSuffix);
    
    return R;
}

Path buildSingle(int value)
{
    return Path(value);
}

Path combine(const Path& A, const Path& B)
{
    Path C;

    C.sum = A.sum + B.sum;

    C.maxPrefix = max(A.maxPrefix, A.sum + B.maxPrefix);
    C.minPrefix = min(A.minPrefix, A.sum + B.minPrefix);

    C.maxSuffix = max(B.maxSuffix, B.sum + A.maxSuffix);
    C.minSuffix = min(B.minSuffix, B.sum + A.minSuffix);

    C.maxSum = max({A.maxSum, B.maxSum, A.maxSuffix + B.maxPrefix});
    C.minSum = min({A.minSum, B.minSum, A.minSuffix + B.minPrefix});

    return C;
}

Path binaryLiftPath(int node, int k)
{
    Path res; 

    for (int i = 0; i < MAXLOG; ++i)
    {
        if (k & (1 << i))
        {
            res  = combine(res, liftPath[node][i]);
            node = liftNode[node][i];
        }
    }
    return res;
}


int lca(int a, int b)
{
    if(depth[a] < depth[b]) swap(a, b);

    int k = depth[a] - depth[b];

    for(int i = 0 ; i < MAXLOG ; ++i)
    {
        if(k & (1 << i))
        {
            a = liftNode[a][i];
        }
    }

    if(a == b) return a;

    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        if(liftNode[a][i] != liftNode[b][i])
        {
            a = liftNode[a][i];
            b = liftNode[b][i];
        }
    }

    return liftNode[a][0];
}

bool query(int a, int b, int k)
{
    int par = lca(a, b);

    int d1 = depth[a] - depth[par];
    int d2 = depth[b] - depth[par];

    Path p1 = binaryLiftPath(a, d1); // A --> LCA
    Path p2 = reversePath(binaryLiftPath(b, d2)); // reversed of B --> LCA (i.e. LCA --> B)

    /*
        * The whole Path is : A --> LCA + LCA + LCA --> B

        * NB : This is needed, because our liftPath array is exclusive
    */
    
    Path res = combine(p1, combine(buildSingle(val[par]), p2));

    return (res.minSum <= k && k <= res.maxSum);
}

void add(int par, int value)
{
    ++cntNodes;

    int u = cntNodes; // u -> currentNode
    val[u] = value;
    depth[u] = depth[par] + 1;

    liftNode[u][0] = par;
    liftPath[u][0] = buildSingle(value);

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prevNode = liftNode[u][i - 1];

        if (prevNode)
        {
            liftNode[u][i] = liftNode[prevNode][i - 1];
            liftPath[u][i] = combine(liftPath[u][i - 1], liftPath[prevNode][i - 1]);
        }
        else
        {
            liftNode[u][i] = 0;
            liftPath[u][i] = liftPath[u][i - 1];
        }

    }
}

void clear()
{
    for (int j = 0; j < MAXLOG; ++j)
    {
        liftNode[0][j] = 0;
        liftPath[0][j] = Path();
    }

    depth[0] = 0; val[0] = 0;

    cntNodes = 0;
}

void solve()
{
    cin >> T;

    for(int rep = 1 ; rep <= T ; ++rep)
    {
        cin >> N;

        add(0, +1);

        char qType;
        int x, y, z;

        for(int i = 1 ; i <= N ; ++i)
        {
            cin >> qType;

            if(qType == '+')
            {
                cin >> x >> y;
                add(x, y);
            }
            else
            {
                cin >> x >> y >> z;
                cout << (query(x, y, z) ? "YES" : "NO") << "\n";
            }
        }

        clear();
    }
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
    
    return 0;
}
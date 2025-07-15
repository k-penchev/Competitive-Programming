#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
const int MAXM = 1e5 + 5;
const int MAXK = 1e4 + 5;
const int LOG = 10;

struct Edge{
    int from;
    int to;
    int w;
};

int n, m, k;

vector<Edge> g(MAXM);
vector<vector<pair<int, int>>> mst(MAXN);
vector<int> depth(MAXN);
vector<vector<int>> up(MAXN, vector<int>(LOG));
vector<vector<int>> max_distance(MAXN, vector<int>(LOG));

struct DSU {
    int par[MAXN], sz[MAXN];

    void init() {
        for(int i = 0; i < MAXN; i++){
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find(int x) {
        return par[x] == x ? x : par[x] = find(par[x]);
    }

    void union_sets(int a, int b) {
        a = find(a), b = find(b);
        if(a != b) {
            if(sz[a] < sz[b]) swap(a, b);
            par[b] = a;
            sz[a] += sz[b];
        }
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};

void dfs(int node, int par, int dep, int dist){
    up[node][0] = par;
    max_distance[node][0] = dist;
    depth[node] = dep;

    for(auto& to : mst[node]){
        if(to.first == par) continue;
        dfs(to.first, node, dep + 1, to.second);
    }
}

void precompute(){

    for(int j = 1; j < LOG; j++){
        for(int i = 0; i < n - 1; i++){
            int prev = up[i][j - 1];

            if(prev == -1){
                up[i][j] = -1;
                max_distance[i][j] = -1;
            }
            else{
                up[i][j] = up[prev][j - 1];
                max_distance[i][j] = max(max_distance[i][j], max_distance[prev][j - 1]);
            }
        }
    }
}

int get_max_weight(int a, int b){
    if(depth[a] < depth[b]) swap(a, b);

    int max_d = 0;    
    int k = depth[a] - depth[b];

    for(int i = 0; i < LOG; i++){
        if((1 << i) && k){
            a = up[a][i];
            max_d = max(max_d, max_distance[a][i]);
        }
    }

    if(a == b){
        return max_d;
    }


    for(int i = 0; i < LOG; i++){
        if( (up[a][i] != up[b][i]) && (up[a][i] != -1) && (up[b][i] != -1) ){
            a = up[a][i];
            b = up[b][i];
            max_d = max(max_d, max(up[a][i], up[b][i]));
        }
    }
    
    return max(max_d, up[a][0]);
}

void init(){
    for(int i = 0; i < MAXN; i++){
        fill(up[i].begin(), up[i].end(), -1);
        fill(max_distance[i].begin(), max_distance[i].end(), 0);
    }
}

bool cmp(const Edge& e1, const Edge& e2){
    return e1.w > e2.w;
}

void add_edge(int a, int b, int c){
    mst[a].push_back({b, c});
    mst[b].push_back({a, c});
}

void build_mst(){
    DSU d; d.init();

    sort(g.begin(), g.end(), cmp);

    int counter = n - 1;

    for(auto& edge : g){
        if(counter == 0) break;
        int from = edge.from;
        int to = edge.to;
        int w = edge.w;

        if(!d.connected(from, to)){
            d.union_sets(from, to);
            counter--;
            add_edge(from, to, w);
        }
    }
}

void solve(){
    cin >> n >> m >> k;

    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c; --a, --b;
        g.push_back({a, b, c});
    }

    build_mst();
    init();
    dfs(0, -1, 0, 0);
    precompute();

    for(int i = 0; i < k; i++){
        int x, y, ans = 0; cin >> x >> y; --x, --y;
        cout << get_max_weight(x, y) << '\n';
    }
}

void speed(){
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main(){ 
    speed();
    solve();
}
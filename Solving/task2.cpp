#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int MAXN = 2 * 1e5 + 5;
const int MAXM = 3 * 1e5 + 5;
const ll INF = INT_MAX;

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

struct Edge {
    int from;
    int to;
    int risk;
    int cost;
};

struct to_node {
    int to;
    int risk;
    int cost;
};

int n, m;
vector<Edge> g1(MAXM);
vector<vector<to_node>> g2(MAXN);
vector<vector<to_node>> mst(MAXM);

int max_risk; 
int cost_sum;

priority_queue<pair<int,int>> pq;
vector<int> dist(MAXN, INF);

void dijkstra(int node, int limit){ 
    fill(dist.begin(), dist.begin() + n, INF);
    while(!pq.empty()) pq.pop();

    pq.push({0, node});
    dist[node] = 0;

    while(!pq.empty()){
        int nd = pq.top().second;
        int nd_dist = -pq.top().first;
        pq.pop();

        if(nd_dist > dist[nd]) continue;

        for(auto& to : g2[nd]){
            if(to.cost > limit) continue; 
            int nxt = to.to;
            int nxtDist = dist[nd] + to.cost;

            if(nxtDist < dist[nxt]){
                dist[nxt] = nxtDist;
                pq.push({-nxtDist, nxt});
            }
        }
    }
}

bool check(int x){
    dijkstra(0, x);                
    if(dist[n - 1] <= x) return 1;
    return 0;
}

void binary_search(){
    int lo = 0, hi = INT_MAX;
    while(lo <= hi){
        int mid = lo + (hi - lo) / 2; 
        if(check(mid)){
            cost_sum = mid;
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }
}

void dfs(int node, int par){                       
    if(node + 1 == n){                             
        return;                                    
    }
    for(auto& t : mst[node]){
        if(t.to == par) continue;
        max_risk = max(max_risk, t.risk); 
        dfs(t.to, node);
    }
}

void add_edge(vector<vector<to_node>>& v, int& a, int &b, int& c, int& d){
    v[a].push_back({b, c, d});
    v[b].push_back({a, c, d});
}

bool cmp(const Edge& e1, const Edge& e2){
    if(e1.risk == e2.risk){
        return e1.cost < e2.cost;
    }
    return e1.risk < e2.risk;
}

void build_mst(){
    DSU d; d.init();

    sort(g1.begin(), g1.begin() + m, cmp);

    int counter = g1.size();
    for(auto& edge : g1){
        if(counter == 0) break;
        int from = edge.from;
        int to = edge.to;
        int risk = edge.risk;
        int cost = edge.cost;

        if(!d.connected(from, to)){
            d.union_sets(from, to);
            add_edge(mst, from, to, risk, cost);
            counter--;
        }
    }
}

void solve(){
    cin >> n >> m;
    for(int i = 0; i < m ; i++){
        int a, b, c, d; cin >> a >> b >> c >> d;
        --a; --b;
        g1[i] = {a, b, c, d};
        add_edge(g2, a, b, c, d);
    }

    build_mst();
    dfs(0, -1);
    binary_search();

    cout << max_risk << " " << cost_sum << '\n';
}

void speed(){
    ios :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main(){
    speed();
    solve();
    return 0;
}

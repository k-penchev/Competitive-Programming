#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;
const double MAXM = 2 * 1e9;

struct to_node{
    int node;
    int percent;
    int boosted;
};

int n;
vector<vector<to_node>> tree(MAXN);
vector<double> water(MAXN), flow(MAXN);

double answer;

void dfs(int node, int par){

    for(auto& to : tree[node]){
        double normal = (to.percent / 100.0) * flow[node];
        if(to.boosted){
            double squared = pow(normal, 2);
            flow[to.node] = max(normal, squared);
        }
        else{
            flow[to.node] = normal;
        }

        dfs(to.node, node);
    }
}

bool check(double x){
    fill(flow.begin(), flow.end(), 0);
    flow[0] = x;

    dfs(0, -1);

    for(int i = 0; i < n; i++){
        if(water[i] == -1) continue;
        else if(water[i] > flow[i]) return false;
    }

    return true;
}

void binary_search(){
    double lo = 0, hi = MAXM;

    for(int i = 0; i < 60; i++){
        double mid = lo + (hi - lo) / 2.0;

        if(check(mid)){
            answer = mid;
            hi = mid;
        }
        else{
            lo = mid;
        }
    }

    cout << fixed << setprecision(4) << answer << endl;
}

void solve(){
    cin >> n;

    for(int i = 0; i < n - 1; i++){
        int a, b, c, d; cin >> a >> b >> c >> d;
        --a, --b;
        tree[a].push_back({b, c, d});
        //tree[b].push_back({a, c, d});
    }

    for(int i = 0; i < n; i++){
        cin >> water[i];
    }

    binary_search();
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
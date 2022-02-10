template<typename T> 
vector<vector<T>> Floyd(vector<vector<pair<int, T>>> adj, T mx) {
    int n = adj.size();
    vector<vector<T>> dist(n, vector<T>(n, mx));

    for(int i = 0;i < n; ++i) {
        dist[i][i] = 0;
        for(auto x: adj[i]) {
            dist[i][x.first] = min(dist[i][x.first], x.second);
        }
    }

    for(int k = 0;k < n; ++k) {
        for(int i = 0;i < n; ++i) {
            for(int j = 0;j < n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    return dist;
    //adjlist, maxvalue
}

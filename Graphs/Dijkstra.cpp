template<typename T>
pair<vector<T>, vector<int>> Dijkstra(int start, vector<vector<pair<int,T>>> adj, T mx) {
    int n = adj.size();
    priority_queue<pair<T, int>> q;

    vector<T> dist(n, mx);
    vector<int> parent(n, -1); 
    dist[start] = 0;

    q.push({0, start});

    while(!q.empty()) {
        int u = q.top().second;
        T dist_u = -q.top().first;
        q.pop();
        if(dist_u != dist[u]) continue;

        for(auto x: adj[u]) {
            int v = x.first;
            T w = x.second;

            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                q.push({-dist[v], v});
            }
        }
    }

    return {dist, parent};
    //start, adjlist, fill_max
}

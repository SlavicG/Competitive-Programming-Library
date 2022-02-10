namespace StronglyConnectedComponents{
    void toposort(int u, vector<bool>& vis, vector<int>& order, vector<vector<int>>& adj) {
        vis[u] = true;
        for(int v: adj[u]) {
            if(!vis[v]) toposort(v, vis, order, adj);
        }
        order.push_back(u);
    }

    void dfs(int u, vector<vector<int>>& g, vector<bool>& vis, vector<int>& component) {
        vis[u] = true;
        component.push_back(u);
        for(int v: g[u]) {
            if(!vis[v]) dfs(v, g, vis, component);
        }
    }

    tuple<vector<vector<int>>, vector<int>, vector<vector<int>>, vector<int>> SCC(vector<vector<int>> adj) {
        int n = adj.size();
        vector<vector<int>> rev_adj(n), c;
        for(int i = 0; i < n ; ++i) {
            for(int j: adj[i]) {
                rev_adj[j].push_back(i);
            }
        }
        vector<int> order;
        vector<bool> vis(n, false);
        for(int i = 0;i < n; ++i) {
            if(!vis[i]) {
                toposort(i, vis, order, adj);
            }
        }
        reverse(order.begin(), order.end());

        vector<int> component;
        vis.assign(n, false);
        for(int u: order) {
            if(!vis[u]) {
                dfs(u, rev_adj, vis, component);
                c.push_back(component);
                component.clear();
            }
        }
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);


        vector<int> t;

        for(auto x: c) {
            t.push_back(x[0]);
            for(int i = 0;i < x.size(); ++i) {
                parent[x[i]] = x[0];
            }
        }

        vector<vector<int>> g(n);
        for(int i = 0;i < n; ++i) {
            for(int j: adj[i]) {
                int u = parent[i], v = parent[j];
                if(u == v) continue;
                g[u].push_back(v);
            }
        }
        return tie(c, parent, g, t);
    }

    //returns tuple of separate components, node responsible for component of node i 
    //condensation graph and topological ordering
}
using namespace StronglyConnectedComponents;

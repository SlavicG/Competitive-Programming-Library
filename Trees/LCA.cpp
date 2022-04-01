struct LCA {
    int n, k, root;
    vector<vector<int>> adj, st;
    vector<int> depth, order, pos;

    void dfs(int u, int par) {
        order.push_back(u);
        for(int v: adj[u]) {
            if(v == par) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            order.push_back(u);
        }
    }
    int merge(int a, int b) {
        return (depth[a] < depth[b] ? a : b);
    }
    int query(int l, int r) {
        int j = 31 - __builtin_clz(r - l + 1);
        return merge(st[j][l], st[j][r - (1 << j) + 1]);
    }
    LCA (vector<vector<int>> g, int _root) {
        root = _root;
        adj = g;
        depth.assign((int)g.size(), 0);
        pos.resize((int)g.size());
        dfs(root, -1);

        n = order.size();
        k = 31 - __builtin_clz(n);
        st.assign(k + 1, vector<int>(n + 1));

        for(int i = n - 1;i >= 0; --i) {
            pos[order[i]] = i;
        }

        for(int i = 0;i < n; ++i) st[0][i] = order[i];

        for(int j = 1;j <= k; ++j) {
            for(int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = merge(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    int lca(int a, int b) {
        if(pos[a] > pos[b]) swap(a, b);
        return query(pos[a], pos[b]);
    }
    int distance(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }
};

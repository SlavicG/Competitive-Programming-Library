namespace MST {
    struct DSU {
        vector<int> p;
        DSU(int n) {p.assign(n, -1);}
        int get(int a) {
            return p[a] < 0 ? a : p[a] = get(p[a]);
        }
        bool uni(int a, int b) {
            a = get(a), b = get(b);
            if(a == b) return false;
            if(p[a] > p[b]) swap(a, b);
            p[a] += p[b]; 
            p[b] = a;
            return true;
        }
        int getsize(int a) {
            return -p[get(a)];
        }
        bool sameset(int a, int b) {
            return (get(a) == get(b));
        }
    };
    
    template<typename T>
    pair<T, vector<vector<pair<int, T>>>> MST(vector<vector<pair<int, T>>> adj) {
        int n = adj.size();
        vector<pair<T, pair<int, int>>> edge;
        for(int i = 0; i < n; i++) {
            for(auto v : adj[i]) {
                edge.push_back({v.second, {i, v.first}});
            }
        }
        sort(edge.begin(), edge.end());
        DSU dsu(n);
        T mincost = 0;
        vector<vector<pair<int, T>>> adjMST(n);
        for(auto x : edge) {
            if(!dsu.sameset(x.second.first, x.second.second)) {
                dsu.uni(x.second.first, x.second.second);
                mincost+=x.first;
                adjMST[x.second.first].push_back({x.second.second, x.first});
                adjMST[x.second.second].push_back({x.second.first, x.first});
            }
        }
        if(dsu.getsize(0) != n) {
            mincost = -1;
        }
        return {mincost, adjMST};
    }
}
using namespace MST;

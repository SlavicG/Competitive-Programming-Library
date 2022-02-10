struct DSU {
	vector<int> e;
	DSU(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};
template<typename T>
pair<T, vector<vector<pair<int, T>>>> MST(vector<vector<pair<int, T>>> adj)
{
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
		if(!dsu.sameSet(x.second.first, x.second.second))
		{
			dsu.join(x.second.first, x.second.second);
			mincost+=x.first;
			adjMST[x.second.first].push_back({x.second.second, x.first});
			adjMST[x.second.second].push_back({x.second.first, x.first});
		}
	}
	if(dsu.size(0) != n)
	{
		mincost = -1;
	}
	return {mincost, adjMST};
}

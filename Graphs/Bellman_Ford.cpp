template<typename T>
tuple<vector<T>, vector<int>, int> bellman_ford(int start, vector<vector<pair<int, T>>>& adj, T mx)
{
	struct edge
	{
		int a, b;
		T w;
	};
	int n = adj.size();
	vector<int> p(n, -1);
	vector<T> d(n, mx);
	d[start]=0;
	int f = -1;
	vector<edge> e;
	int index = 0;
	for(auto x : adj)
	{
		for(auto y : x)
		{
			edge now;
			now.a = index;
			now.b = y.first;
			now.w = y.second;
			e.push_back(now);
		}
		index++;
	}
	for(int i = 0; i < n+1; i++) {
		f=-1;
		for (auto x : e) {
			if (d[x.a]+x.w<d[x.b]) {
				d[x.b] = d[x.a]+x.w;
				p[x.b] = x.a;
				f=x.b;
			}
		}
	}
	if (f == -1){return {d, p, -1};}
	else{return {d, p, f};}
	//returns distance, parent array, if negative cycle it returns element in cycle.
	//tie(A, B, C) = bellman_ford(s, adj, (ll)1e18);
}

template<typename T>
pair<T, vector<int>> diameter(vector<vector<pair<int, T>>> adj)
{
	int n = adj.size();
	stack<pair<int, T>> q;
	q.push({0, (T)0});
	vector<int> p(n, -1);
	p[0] = -2;
	T distance_max = -1;
	int opposite_node = -1;
	while(!q.empty())
	{
		int node = q.top().first;
		T dist = q.top().second;
		if(dist >= distance_max){distance_max = dist; opposite_node = node;}
		q.pop();
		for(auto v : adj[node])
		{
			if(p[v.first] == -1)
			{
				p[v.first] = node;
				q.push({v.first, dist+v.second});
			}
		}
	}
	p.assign(n, -1);
	q.push({opposite_node, (T)0});
	p[opposite_node] = -2;
	opposite_node = -1;
	distance_max = -1;
	while(!q.empty())
	{
		int node = q.top().first;
		T dist = q.top().second;
		if(dist >= distance_max){distance_max = dist; opposite_node = node;}
		q.pop();
		for(auto v : adj[node])
		{
			if(p[v.first] == -1)
			{
				p[v.first] = node;
				q.push({v.first, dist+v.second});
			}
		}
	}
	vector<int> path;
	int now = opposite_node;
	while(now != -2)
	{
		path.push_back(now);
		now = p[now];
	}
	return {distance_max, path};
}

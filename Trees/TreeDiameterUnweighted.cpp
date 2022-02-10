template<typename T>
pair<int, vector<int>> diameter(vector<vector<T>> adj)
{
	int n = adj.size();
	stack<pair<int, int>> q;
	q.push({0, 0});
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
			if(p[v] == -1)
			{
				p[v] = node;
				q.push({v, dist+1});
			}
		}
	}
	p.assign(n, -1);
	q.push({opposite_node, 0});
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
			if(p[v] == -1)
			{
				p[v] = node;
				q.push({v, dist+1});
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

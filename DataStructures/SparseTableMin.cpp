template<typename T>
struct SparseTableMin{
	int n;
	vector<vector<pair<T, int>>> table;
	SparseTable(vector<T> a){
		int n = a.size();
		int max_size = 31-__builtin_clz(n);
		table.assign(n, vector<pair<T, int>>(max_size+1, {(T)0,0}));
		for(int i = 0; i < n; i++){
			table[i][0].first = a[i];
			table[i][0].second = i;
		}
		for(int i = 1; i <= max_size; i++) {
			int power = 1<<i;
			for(int j = 0; j <= n-power; j++) {
				table[j][i].first = min(table[j][i-1].first,table[j+power/2][i-1].first);
				table[j][i].second = table[j][i-1].first < table[j+power/2][i-1].first ? table[j][i-1].second : table[j+power/2][i-1].second;
			}
		}
	}
	pair<T, int> query(int l, int r)
	{
		int dist = 31-__builtin_clz(r-l+1);
		return {min(table[l][dist].first, table[r-(1<<dist)+1][dist].first), table[l][dist].first < table[r-(1<<dist)+1][dist].first ? table[l][dist].second : table[r-(1<<dist)+1][dist].second};
	}
};

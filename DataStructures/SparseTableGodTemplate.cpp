template<typename T>
struct SparseTable{
	int n;
	vector<vector<T>> table;
	function<T(const T&, const T&)> merge;
	SparseTable(vector<T> a, const function<T(const T&, const T&)> &_merge){
		int n = a.size();
		merge = _merge;
		int max_size = 31-__builtin_clz(n);
		table.assign(max_size+1, vector<T>(n, (T)0));
		for(int i = 0; i < n; i++){
			table[0][i] = a[i];
		}
		for(int i = 1; i <= max_size; i++) {
			for(int j = 0; j <= n-(1<<i); j++) {
				table[i][j] = merge(table[i-1][j],table[i-1][j+(1<<(i-1))]);
			}
		}
	}
	T query(int l, int r)
	{
		int dist = 31-__builtin_clz(r-l+1);
		return merge(table[dist][l], table[dist][r-(1<<dist)+1]);
	}
};

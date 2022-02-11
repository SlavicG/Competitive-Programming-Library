template<typename T, bool return_index> 
struct range_max_query{
    int n, k;
    vector<vector<int>> st;
    vector<T> a;
    int merge(int x, int y) {
        return (a[x] >= a[y] ? x : y);
    }

    range_max_query(vector<T> A) {
        n = A.size();
        a = A;
        k = 31 - __builtin_clz(n);
        st.assign(k + 1, vector<int>(n + 1, 0));
        for(int i = 0;i < n; ++i) st[0][i] = i;

        for(int j = 1; j <= k; ++j) {
            for(int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = merge(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int j = 31 - __builtin_clz(r - l + 1);
        int idx = merge(st[j][l], st[j][r - (1 << j) + 1]);
        return (return_index ? idx : a[idx]);
    }
};

template<typename T, bool zero_indexing>
struct fenwick_tree {
    int N;
    vector<T> fen;
    fenwick_tree(int n) {
        N = n, fen.assign(n + 1, 0);
    }
    fenwick_tree(vector<T> a) {
        N = a.size();
        fen.assign(N + 1, 0);
        for(int i = 0; i < N; ++i) {
            add(i, a[i]);
        }
    }
    void add(int p, T val) {
        for(int i = p + zero_indexing;i <= N;i += i & -i) {
            fen[i] += val;
        }
    }
    void set(int p, T val) {
        T set_val = val - query(p, p);
        add(p, set_val);
    }

    T query(int l, int r) {
        T ret = 0;
        for(int i = r + zero_indexing; i >= 1; i -= i & -i) {
            ret += fen[i];
        }   
        for(int i = l + zero_indexing - 1; i >= 1; i -= i & -i) {
            ret -= fen[i];
        }   
        return ret;
    }
};

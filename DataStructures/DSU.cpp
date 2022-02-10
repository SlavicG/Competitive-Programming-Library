struct DSU{
    vector<int> p;
    DSU(int n) {
        p.assign(n, -1);
    }
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
    bool sameset(int a, int b) {
        return (get(a) == get(b));
    }
};

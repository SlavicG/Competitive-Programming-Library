struct PolynomialSegmentTree {
    vector<ll> lazy1, lazy2, t;
    int n;
    ll sum(ll x) {return x * (x + 1) / 2;}
    PolynomialSegmentTree(int _n) {
        n = _n;
        t.assign(4 * n, 0);
        lazy1.assign(4 * n, 0);
        lazy2.assign(4 * n, 0);
    }

    void push1(int i, int l, int r) {
        if(!lazy1[i]) return;
        t[i] += lazy1[i] * (sum(r + 1) - sum(l));
        if(l != r) {
            lazy1[2 * i] += lazy1[i];
            lazy1[2 * i + 1] += lazy1[i];
        }
        lazy1[i] = 0;
    }
    void push2(int i, int l, int r) {
        if(!lazy2[i]) return;
        t[i] += lazy2[i] * (r - l + 1);
        if(l != r) {
            lazy2[2 * i] += lazy2[i];
            lazy2[2 * i + 1] += lazy2[i];
        }
        lazy2[i] = 0;
    }

    void modif1(int i, int l, int r, int tl, int tr, ll val) {
        push1(i, l, r);
        push2(i, l, r);
        if(l > tr || r < tl) return;
        if(l >= tl && r <= tr) {
            lazy1[i] += val;
            push1(i, l, r);
            return;
        }
        int mid = l + r >> 1;
        modif1(2 * i, l, mid, tl, tr, val);
        modif1(2 * i + 1, mid + 1, r, tl, tr, val);
        t[i] = t[2 * i] + t[2 * i + 1];
    }
    void modif2(int i, int l, int r, int tl, int tr, ll val) {
        push1(i, l, r);
        push2(i, l, r);
        if(l > tr || r < tl) return;
        if(l >= tl && r <= tr) {
            lazy2[i] += val;
            push2(i, l, r);
            return;
        }
        int mid = l + r >> 1;
        modif2(2 * i, l, mid, tl, tr, val);
        modif2(2 * i + 1, mid + 1, r, tl, tr, val);
        t[i] = t[2 * i] + t[2 * i + 1];
    }


    ll query(int i, int l, int r, int tl, int tr) {
        push1(i, l, r);
        push2(i, l, r);
        if(l > tr || r < tl) return 0;
        if(l >= tl && r <= tr) return t[i];
        int mid = l + r >> 1;
        return query(2 * i, l, mid, tl, tr) + query(2 * i + 1, mid + 1, r, tl, tr);
    }

    void add_constant(int l, int r, ll val) {
        modif2(1, 0, n - 1, l, r, val);
    }
    void add_constant(int i, ll val) {
        modif2(1, 0, n - 1, i, i, val);
    }
    void add_polynomial(int l, int r, ll val) {
        modif1(1, 0, n - 1, l, r, val);
    }
    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
    ll query(int l) {
        return query(1, 0, n - 1, l, l);
    }
};

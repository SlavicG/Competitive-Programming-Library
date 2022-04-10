struct LiChaoTree {
    bool (*cmp)(ll,ll);
    ll neutral;
    struct line {
        ll m, c; 
        line(ll M, ll C) : m(M), c(C) {}
        line(){}
        ll f(ll x) {return m * x + c;}
    };

    struct node {
        node* left, *right;
        line k;
        ll l, r, mid;
        LiChaoTree *p;
        node(ll _l, ll _r, line _k, LiChaoTree* _p) {
            l = _l; r = _r; k = _k; mid = l + (r - l) / 2;
            p = _p;
            left = right = NULL;
        }

        void add_line(line a) {
            if(!p->cmp(a.f(l), k.f(l)) && !p->cmp(a.f(r), k.f(r))) return;
            if(p->cmp(a.f(l), k.f(l)) && p->cmp(a.f(r), k.f(r))) {k = a; return;}

            if(p->cmp(a.f(mid), k.f(mid))) swap(a, k);

            if(!left) left = new node(l, mid, k, p);
            if(!right) right = new node(mid + 1, r, k, p);

            if(p->cmp(a.f(l), k.f(l))) left->add_line(a);
            else right->add_line(a);
        }
    };

    node* root;

    ll query(node* u, ll x) {
        if(!u) return neutral;
        if(x > u->r || x < u->l) return neutral;
        ll val1 = u->k.f(x), val2 = query(u->left, x), val3 = query(u->right, x);
        if(cmp(val2, val1)) val1 = val2;
        if(cmp(val3, val1)) val1 = val3;
        return val1;
    }

    LiChaoTree(ll _l, ll _r, ll _neutral,  bool (*_cmp)(ll,ll), ll _m, ll _c) {
        root = new node(_l, _r, {_m, _c}, this);
        neutral = _neutral;
        cmp = _cmp;
    }

    ll query(ll x) {return query(root, x);}
    void add_line(line l) {root->add_line(l);}
    //leftbound, rightbound, neutral value, comparator, line parameters: m, c.
};

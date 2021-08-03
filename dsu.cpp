struct Dsu {
    int n; std::vector<int> par;

    Dsu() : n(0) {}
    Dsu(int _n) : n(_n) { par.assign(_n, -1); }

    int find(int x) { return par[x] < 0 ? x : par[x] = find(par[x]); }
    bool same(int u, int v) { return find(u) == find(v); }
    bool unite(int u, int v) {
        if ((u = find(u)) == (v = find(v))) return false;
        if (par[v] < par[u]) std::swap(u, v); par[u] += par[v]; par[v] = u; return true;
    }
};

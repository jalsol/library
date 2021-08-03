template <bool VALS_IN_EDGE> struct Hld {
    std::vector<int> sz, par, dep, pos, head;
    std::vector<std::vector<int>> g;
    int timer = 0;
    int n;

    Hld() : n(0) {}
    Hld(int _n) : n(_n + 5) { sz.resize(_n + 5); par.resize(_n + 5); dep.resize(_n + 5); pos.resize(_n + 5); head.resize(_n + 5); g.resize(_n + 5); }

    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }

    void DfsSz(int u = 1) {
        sz[u] = 1;
        for (int &v : g[u]) {
            par[v] = u; dep[v] = dep[u] + 1;
            g[v].erase(std::find(begin(g[v]), end(g[v]), u));
            DfsSz(v); sz[u] += sz[v];
            if (sz[v] > sz[g[u].front()]) std::swap(v, g[u].front());
        }
    }

    void DfsHld(int u = 1) {
        pos[u] = ++timer;
        for (int &v : g[u]) head[v] = (v == g[u].front() ? head[u] : v), DfsHld(v);
    }

    void updateHld(int u, int v, int delta) {
        for (; head[u] != head[v]; v = par[head[v]]) {
            if (dep[head[u]] > dep[head[v]]) std::swap(u, v);
            // updateTree(pos[head[v]], pos[v], delta);
        }

        if (dep[u] > dep[v]) std::swap(u, v);
        // updateTree(pos[u] + VALS_IN_EDGE, pos[v], delta);
    }

    long long queryHld(int u, int v) {
        long long ret = 0;
        for (; head[u] != head[v]; v = par[head[v]]) {
            if (dep[head[u]] > dep[head[v]]) std::swap(u, v);
            // ret += queryTree(pos[head[v]], pos[v];
        }

        if (dep[u] > dep[v]) std::swap(u, v);
        // ret += queryTree(pos[u] + VALS_IN_EDGE, pos[v]);
        return ret;
    }
};

struct Centroid {
    int n, k, maxdepth;
    long long ans;
    std::vector<int> sz;
    std::vector<long long> min;
    std::vector<bool> processed;
    std::vector<std::vector<std::pair<int, int>>> g;

    const long long inf = 1e18;

    Centroid() : n(0) {}
    Centroid(int _n) : n(_n + 5) { sz.resize(_n + 5); min.resize(_n + 5); processed.resize(_n + 5); g.resize(_n + 5); }

    void addEdge(int u, int v, int c) { g[u].emplace_back(v, c); g[v].emplace_back(u, c); }

    int getSz(int u, int p = 0) {
        sz[u] = 1;
        for (const auto &[v, c] : g[u])
            if (!processed[v] && v != p)
                sz[u] += getSz(v, u);
        return sz[u];
    }

    int getCen(int u, int tsz, int p = 0) {
        for (const auto &[v, c] : g[u])
            if (!processed[v] && v != p && sz[v] * 2 > tsz)
                return getCen(v, tsz, u);
        return u;
    }

    void getAns(int u, int p, long long sum, bool mark, int depth = 1) {
        if (depth > k) return; maxdepth = std::max(maxdepth, depth);

        if (mark) min[depth] = std::min(min[depth], sum);
        else ans = std::min(ans, sum + min[k - depth]);

        for (const auto &[v, c] : g[u])
            if (!processed[v] && v != p)
                getAns(v, u, sum + c, mark, depth + 1);
    }

    void solveCen(int u) {
        u = getCen(u, getSz(u)); processed[u] = true; min[0] = 0; maxdepth = 0;

        for (const auto &[v, c] : g[u])
            if (!processed[v])
                getAns(v, u, c, false), getAns(v, u, c, true);

        std::fill_n(begin(min) + 1, maxdepth, inf);
        for (const auto &[v, c] : g[u])
            if (!processed[v]) solveCen(v);
    }

    long long solve(int _k) {
        ans = inf; k = _k; maxdepth = 0;
        std::fill(begin(sz), end(sz), 0);
        std::fill(begin(min), end(min), inf);
        std::fill(begin(processed), end(processed), false);
        solveCen(1);
        return ans;
    }
};

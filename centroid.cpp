#include <vector>

template <class T> struct Centroid {
    int n, k, maxdepth; T ans;
    std::vector<int> sz;
    std::vector<T> min;
    std::vector<bool> rem;
    std::vector<std::vector<std::pair<int, int>>> g;

    // TODO: modify this
    static constexpr T inf = 1e9;

    Centroid() : n(0) {}
    Centroid(int _n)
        : n(_n + 5), sz(_n + 5), min(_n + 5), rem(_n + 5), g(_n + 5) {}

    void addEdge(int u, int v, int c) {
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }

    int __getSz(int u, int p = 0) {
        sz[u] = 1;
        for (const auto& [v, c] : g[u])
            if (!rem[v] && v != p)
                sz[u] += __getSz(v, u);
        return sz[u];
    }

    int __getCen(int u, int tsz, int p = 0) {
        for (const auto& [v, c] : g[u])
            if (!rem[v] && v != p && sz[v] * 2 > tsz)
                return __getCen(v, tsz, u);
        return u;
    }

    void __getAns(int u, int p, T sum, bool mark, int depth = 1) {
        if (depth > k) return; maxdepth = std::max(maxdepth, depth);

        if (mark) min[depth] = std::min(min[depth], sum);
        else ans = std::min(ans, sum + min[k - depth]);

        for (const auto& [v, c] : g[u])
            if (!rem[v] && v != p)
                __getAns(v, u, sum + c, mark, depth + 1);
    }

    void __solveCen(int u) {
        u = __getCen(u, __getSz(u)); rem[u] = true; min[0] = 0; maxdepth = 0;

        for (const auto& [v, c] : g[u])
            if (!rem[v])
                __getAns(v, u, c, false), __getAns(v, u, c, true);

        std::fill_n(begin(min) + 1, maxdepth, inf);
        for (const auto& [v, c] : g[u])
            if (!rem[v]) __solveCen(v);
    }

    T solve(int _k) {
        ans = inf; k = _k; maxdepth = 0;
        std::fill(sz.begin(), sz.end(), 0);
        std::fill(min.begin(), min.end(), inf);
        std::fill(rem.begin(), rem.end(), false);
        __solveCen(0);
        return ans;
    }
};

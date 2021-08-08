template <class T> struct Dinic {
    struct Edge { int v; T cap, flow; };
    int n;
    std::vector<std::vector<int>> g;
    std::vector<int> ptr, level;
    std::vector<Edge> edge;

    // TODO: modify this
    static constexpr T __inf = 1e9;

    Dinic() : n(0) {}
    Dinic(int _n) : n(_n), g(_n, std::vector<int>()), ptr(_n), level(_n) {}

    void addEdge(int u, int v, T c) {
        int k = static_cast<int>(edge.size());
        edge.push_back({v, c, 0}); edge.push_back({u, c, c});
        g[u].push_back(k); g[v].push_back(k ^ 1);
    }

    bool __Bfs(int s, int t) {
        std::queue<int> q; q.push(s);
        std::fill(level.begin(), level.end(), -1); level[s] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i : g[u]) {
                const Edge& e = edge[i];
                if (level[e.v] == -1 && e.flow < e.cap) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }

        return level[t] != -1;
    }

    T __Dfs(int u, int t, T amount) {
        if (u == t) return amount;

        for (int& i = ptr[u]; i < static_cast<int>(g[u].size()); i++) {
            const Edge& e = edge[g[u][i]];
            if (level[e.v] != level[u] + 1) continue;

            if (e.flow < e.cap) {
                T a = __Dfs(e.v, t, std::min(amount, e.cap - e.flow));
                if (a > 0) {
                    edge[g[u][i]].flow += a;
                    edge[g[u][i] ^ 1].flow -= a;
                    return a;
                }
            }
        }

        return 0;
    }

    T flow(int s, int t, T mx = __inf) {
        T ret = 0;
        while (__Bfs(s, t)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            for (;;) {
                T augment = __Dfs(s, t, mx - ret);
                if (augment == 0) break;
                ret += augment;
            }
        }

        return ret;
    }
};

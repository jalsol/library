#include "rmq.cpp"

#include <vector>
#include <tuple>
#include <algorithm>

struct LCA {
    int timer = 0;
    std::vector<int> tin, path, ret, dep;
    RMQ<int> rmq;

    LCA(const std::vector<std::vector<int>>& g)
        : tin(g.size()), dep(g.size()), rmq((dfs(g, 0, -1), ret))
    {
        path.reserve(g.size());
        ret.reserve(g.size());
    }

    void dfs(const std::vector<std::vector<int>>& g, int u, int par) {
        tin[u] = timer++;
        for (int v : g[u]) {
            if (v != par) {
                dep[v] = dep[u] + 1;
                path.push_back(u), ret.push_back(tin[u]);
                dfs(g, v, u);
            }
        }
    }

    int lca(int a, int b) {
        if (a == b) return a;
        std::tie(a, b) = std::minmax(tin[a], tin[b]);
        return path[rmq.query(a, b)];
    }

    int dist(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[lca(a,b)];
    }
};

#include <vector>

struct Dsu {
    std::vector<int> par;

    Dsu() {}
    Dsu(int n) : par(n, -1) {}

    int find(int x) {
        while (par[x] >= 0) {
            if (par[par[x]] >= 0) par[x] = par[par[x]];
            x = par[x];
        }
        return x;
    }

    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) std::swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }

    int size(int x) {
        return -par[find(x)];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }
};

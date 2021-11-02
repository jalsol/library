#include "impliseg.cpp"

#include <vector>
#include <algorithm>

template <bool VALS_EDGES> struct HLD {
    int N, timer = 0;
    std::vector<std::vector<int>> g;
    std::vector<int> par, sz, dep, root, pos;

    Node* tree;

    HLD(const std::vector<std::vector<int>>& _g)
        : N(_g.size()), g(_g), par(N, -1), sz(N, 1), dep(N),
          root(N), pos(N), tree(new Node(0, N))
    {
        DfsSz(0); DfsHld(0);
    }

    void DfsSz(int v) {
        if (par[v] != -1) {
            g[v].erase(std::find(g[v].begin(), g[v].end(), par[v]));
        }

        for (int &u : g[v]) {
            par[u] = v;
            dep[u] = dep[v] + 1;

            DfsSz(u);

            sz[v] += sz[u];
            if (sz[u] > sz[g[v].front()]) {
                std::swap(u, g[v].front());
            }
        }
    }

    void DfsHld(int v) {
        pos[v] = timer++;
        for (int u : g[v]) {
            root[u] = (u == g[v].front() ? root[v] : u);
            DfsHld(u);
        }
    }

    template <class B> void process(int u, int v, B op) {
        for (; root[u] != root[v]; v = par[root[v]]) {
            if (dep[root[u]] > dep[root[v]]) std::swap(u, v);
            op(pos[root[v]], pos[v] + 1);
        }

        if (dep[u] > dep[v]) std::swap(u, v);
        op(pos[u] + VALS_EDGES, pos[v] + 1);
    }

    void modifyPath(int u, int v, int val) {
        process(u, v, [&](int l, int r) {
            tree->add(l, r, val);
        });
    }

    int queryPath(int u, int v) {
        int ret = -1e9;
        process(u, v, [&](int l, int r) {
            ret = std::max(ret, tree->query(l, r));
        });
        return ret;
    }

    int querySubtree(int v) {
        return tree->query(pos[v] + VALS_EDGES, pos[v] + sz[v]);
    }
};

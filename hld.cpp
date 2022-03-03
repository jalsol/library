#include <algorithm>

using namespace std;

using ll = long long;

constexpr int maxN = 1e5 + 5;

vector<int> g[maxN];

int sz[maxN];
int par[maxN];
int heavy[maxN];
int dep[maxN];

int Dfs(int u) {
    sz[u] = 1;

    for (int v : g[u]) if (v != par[u]) {
        par[v] = u;
        dep[v] = dep[u] + 1;
        sz[u] += Dfs(v);

        if (sz[heavy[u]] < sz[v]) {
            heavy[u] = v;
        }
    }

    return sz[u];
}

int head[maxN];
int tin[maxN], timer;

void decompose(int u, int lead) {
    head[u] = lead;
    tin[u] = ++timer;

    if (heavy[u]) {
        decompose(heavy[u], lead);
    }

    for (int v : g[u]) if (v != par[u] && v != heavy[u]) {
        decompose(v, v);
    }
}

int query(int u, int v) {
    ll ret = 0;

    for (; head[u] != head[v]; v = par[head[v]]) {
        if (dep[head[u]] > dep[head[v]]) swap(u, v);
        // ret += get(tin[head[v]], tin[v])
    }

    if (dep[u] > dep[v]) swap(u, v);
    // ret += get(tin[u], tin[v]);

    return ret;
}

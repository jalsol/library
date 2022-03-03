#include "lca.cpp"

#define all(x) (x).begin(), (x).end()

int k;
vector<int> a, stk;
vector<int> vg[maxN];

bool upper(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

void addEdge(int u, int v) {
    vg[u].push_back(v);
    vg[v].push_back(u);
}

int buildVirtualTree() {
    sort(all(a), [&](int u, int v) {
        return tin[u] < tin[v];
    });

    for (int i = 1; i < k; ++i) {
        a.push_back(getLca(a[i - 1], a[i]));
    }

    sort(all(a), [&](int u, int v) {
        return tin[u] < tin[v];
    });

    a.erase(unique(all(a)), a.end());
    stk.clear();

    for (int x : a) {
        while (stk.size() > 1 && !upper(stk.back(), x)) {
            addEdge(stk.end()[-2], stk.back());
            stk.pop_back();
        }
        stk.push_back(x);
    }

    while (stk.size() > 1) {
        addEdge(stk.end()[-2], stk.back());
        stk.pop_back();
    }

    return stk[0];
}

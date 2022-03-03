#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

constexpr int maxN = 1e5 + 5;

vector<int> g[maxN];

int sz[maxN];
bool rem[maxN];
int par[maxN];

int getSize(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) if (!rem[v] && v != p) {
        sz[u] += getSize(v, u);
    }
    return sz[u];
}

int getCen(int u, int p, int limit) {
    for (int v : g[u]) if (!rem[v] && v != p) {
        if (sz[v] * 2 > limit) {
            return getCen(v, u, limit);
        }
    }
    return u;
}

// =============================================================================

void buildCen(int u, int p) {
    u = getCen(u, p, getSize(u, p));
    rem[u] = true;
    par[u] = p;

    for (int v : g[u]) if (!rem[v]) {
        buildCen(v, u);
    }
}

void update(int x) {
    for (int u = x; u != -1; u = par[u]) {

    }
}

int get(int x) {
    int ret = 0;

    for (int u = x; u != -1; u = par[u]) {

    }

    return ret;
}

// =============================================================================

int d;
int cnt[maxN];
bool important[maxN];

int maxDist;
ll ans;

void solvePath(int u, int p, int cen, bool fill) {
    int dist /* = getDist(u, cen); */;
    if (dist > d) return;
    maxDist = max(maxDist, dist);

    if (important[u]) {
        if (fill) {
            ++cnt[dist];
        } else {
            ans += cnt[d - dist];
        }
    }

    for (int v : g[u]) if (!rem[v] && v != p) {
        solvePath(v, u, cen, fill);
    }
}

void solveCen(int u) {
    u = getCen(u, -1, getSize(u, -1));
    rem[u] = true;
    cnt[0] = important[u];

    for (int v : g[u]) if (!rem[v]) {
        solvePath(v, u, u, false);
        solvePath(v, u, u, true);
    }

    fill_n(cnt, maxDist + 1, 0);

    for (int v : g[u]) if (!rem[v]) {
        solveCen(v);
    }
}

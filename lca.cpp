#include <vector>
#include <algorithm>

using namespace std;

constexpr int maxN = 1e5 + 5;
constexpr int logN = 20;

vector<int> g[maxN];

int tin[maxN], tout[maxN], timer;
int rmq[2 * maxN][logN], pos;
int dep[maxN];
int lg[2 * maxN];

void Dfs(int u, int p) {
    tin[u] = ++timer;
    rmq[++pos][0] = u;

    for (int v : g[u]) if (v != p) {
        dep[v] = dep[u] + 1;
        Dfs(v, u);
        rmq[++pos][0] = u;
    }

    tout[u] = ++timer;
}

int getHigh(int u, int v) {
    return dep[u] < dep[v] ? u : v;
}

#define PW(x) (1 << (x))

int getLca(int u, int v) {
    int l = tin[u], r = tin[v];
    if (l > r) swap(l, r);

    int j = lg[r - l + 1];
    return getHigh(rmq[l][j], rmq[r - PW(j) + 1][j]);
}

int getDist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[getLca(u, v)];
}

void buildLca() {
    timer = pos = 0;
    Dfs(1, -1);

    for (int i = 2; i < 2 * maxN; ++i) {
        lg[i] = lg[i / 2] + 1;
    }

    for (int j = 1; j < logN; ++j) {
        for (int i = 1; i + PW(j) - 1 <= pos; ++i) {
            rmq[i][j] = getHigh(rmq[i][j - 1], rmq[i + PW(j - 1)][j - 1]);
        }
    }
}

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

using ll = long long;

constexpr int maxN = 1200;
constexpr int maxE = 12e4;

struct Edge {
    int v, cap, flow;
};

int n;
vector<int> g[maxN];
Edge e[maxE];
int eCnt;

void addEdge(int u, int v, int c) {
    e[eCnt] = {v, c, 0};
    e[eCnt + 1] = {u, c, c};
    g[u].push_back(eCnt);
    g[v].push_back(eCnt + 1);
    eCnt += 2;
}

int lvl[maxN];
queue<int> q;

bool Bfs(int s, int t) {
    fill_n(lvl + 1, n, -1);
    lvl[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int id : g[u]) {
            int v = e[id].v;

            if (lvl[v] == -1 && e[id].flow < e[id].cap) {
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
    }

    return lvl[t] != -1;
}

int ptr[maxN];

ll Dfs(int u, int t, ll amount) {
    if (u == t) return amount;

    for (int& i = ptr[u]; i < g[u].size(); ++i) {
        int id = g[u][i];
        int v = e[id].v;

        if (lvl[v] == lvl[u] + 1 && e[id].flow < e[id].cap) {
            ll d = Dfs(v, t, min(amount, e[id].cap - e[id].flow));
            if (d > 0) {
                e[id].flow += d;
                e[id ^ 1].flow -= d;
                return d;
            }
        }
    }

    return 0;
}

ll maxFlow(int s, int t) {
    ll mx = LLONG_MAX;
    ll ret = 0;

    while (Bfs(s, t)) {
        fill_n(ptr + 1, n, 0);

        for (;;) {
            ll d = Dfs(s, t, mx - ret);
            if (d == 0) break;
            ret += d;
        }
    }

    return ret;
}

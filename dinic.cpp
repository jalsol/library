#include <vector>
#include <climits>

struct Dinic {
    struct Edge {
        int to, rev;
        long long cap, oc;
        long long flow() { return std::max(oc - cap, 0LL); }
    };

    std::vector<int> level, ptr, q;
    std::vector<std::vector<Edge>> g;

    Dinic(int n) : level(n), ptr(n), q(n), g(n) {}

    void addEdge(int a, int b, long long cap, long long rcap = 0) {
        g[a].push_back({ b, int(g[b].size()),     cap,  cap  });
        g[b].push_back({ a, int(g[a].size()) - 1, rcap, rcap });
    }

    long long dfs(int v, int t, long long f) {
        if (v == t || !f) return f;

        for (int &i = ptr[v]; i < int(g[v].size()); ++i) {
            Edge &e = g[v][i];
            if (level[e.to] != level[v] + 1) continue;

            if (long long p = dfs(e.to, t, std::min(f, e.cap))) {
                e.cap -= p;
                g[e.to][e.rev].cap += p;
                return p;
            }
        }

        return 0;
    }

    long long calc(int s, int t) {
        long long flow = 0; q[0] = s;

        for (int L = 0; L < 31; ++L) {
            do {
                level = ptr = std::vector<int>(q.size());
                int qi = 0, qe = level[s] = 1;

                while (qi < qe && !level[t]) {
                    int v = q[qi++];
                    for (const Edge &e : g[v]) {
                        if (!level[e.to] && e.cap >> (30 - L)) {
                            q[qe++] = e.to;
                            level[e.to] = level[v] + 1;
                        }
                    }
                }

                while (long long p = dfs(s, t, LLONG_MAX)) {
                    flow += p;
                }

            } while (level[t]);
        }

        return flow;
    }

    bool leftOfMinCut(int a) {
        return level[a] != 0;
    }
};

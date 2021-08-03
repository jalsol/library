template <class T> struct RMQ {
    std::vector<std::vector<T>> st;
    int n, lg;

    // TODO: modify this
    T __op(T x, T y) { return std::min(x, y); }

    int __internal_log2(int x) { assert(x > 0); return 31 - __builtin_popcount(x); }

    RMQ() : n(0), lg(0) {}
    RMQ(const std::vector<T>& v) : n(v.size()), lg(__internal_log2(v.size()) + 2) {
        st.assign(n, std::vector<T>(lg));
        for (int i = 0; i < n; i++) st[i][0] = v[i];
        for (int j = 1; j < lg; j++) for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = __op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }

    T query(int l, int r) { assert(l < r); --r; int j = __internal_log2(r - l + 1); return __op(st[l][j], st[r - (1 << j) + 1][j]); }
};

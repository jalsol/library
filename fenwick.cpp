template <class T> struct Fen {
    int n;
    std::vector<T> fen;

    Fen() : n(0) {}
    Fen(int _n) : n(_n + 5) { fen.assign(_n + 5, 0); }

    void update(int i, T x) { for (++i; i < n; i += (i & -i)) fen[i] += x; }

    T query(int i) {
        T ret = 0;
        for (++i; i > 0; i -= (i & -i)) ret += fen[i];
        return ret;
    }

    T query(int l, int r) { if (l > r - 1) return 0; return query(r - 1) - query(l - 1); }
};

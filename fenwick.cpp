template <class T> struct Fen {
    std::vector<T> fen;
    int n;

    Fen() : n(0) {}
    Fen(int _n) : n(_n + 5) { fen.assign(_n + 5, 0); }

    void update(int i, T x) {
        for (; i < n; i += (i & -i)) {
            fen[i] += x;
        }
    }

    T get(int i) {
        T ret = 0;
        for (; i > 0; i -= (i & -i)) {
            ret += fen[i];
        }
        return ret;
    }

    T get(int l, int r) {
        if (l > r) return 0;
        return get(r) - get(l - 1);
    }
};

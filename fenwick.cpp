#include <vector>

template <class T> struct Fen {
    int n;
    std::vector<int> fen;

    Fen() : n(0) {}
    Fen(int _n) : n(_n), fen(_n) {}

    void update(int pos, T x) {
        for (; pos < n; pos |= pos + 1) {
            fen[pos] += x;
        }
    }

    T query(int pos) {
        T ret = 0;
        for (; pos > 0; pos &= pos - 1) {
            ret += fen[pos - 1];
        }
        return ret;
    }

    T query(int l, int r) {
        return query(r) - query(l);
    }
};

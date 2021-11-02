#include <vector>
#include <climits>

struct Tree {
    using T = int;
    static constexpr T unit = INT_MIN;

    T f(T a, T b) {
        return std::max(a, b);
    }

    int n;
    std::vector<T> s;

    Tree(int _n = 0, T def = unit) : n(_n), s(2 * _n, def) {}

    void update(int pos, T val) {
        for (s[pos += n] = val; pos >>= 1;) {
            s[pos] = f(s[pos << 1], s[pos << 1 | 1]);
        }
    }

    T query(int b, int e) {
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b >>= 1, e >>= 1) {
            if (b & 1) ra = f(ra, s[b++]);
            if (e & 1) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

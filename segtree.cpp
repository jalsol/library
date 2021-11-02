#include <vector>

template <class T> struct Segtree {
    // TODO: modify these
    static constexpr int __m_Id = 0;
    T op(T x, T y) {
        return x + y;
    }

    int n;
    std::vector<T> tree;

    int midof(int l, int r) {
        return l + (r - l) / 2;
    }
    int rnode(int i, int l, int r) {
        int m = midof(l, r);
        return i + (m - l + 1) * 2;
    }
    void pull(int i, int j) {
        tree[i] = op(tree[i + 1], tree[j]);
    }

    void update(int p, const T& x, int i, int l, int r) {
        if (p < l || r < p) return;

        if (l == r) {
            tree[i] = x;
            return;
        }

        int m = midof(l, r);
        int j = rnode(i, l, r);
        if (p <= m) {
            update(p, x, i + 1, l, m);
        }
        else {
            update(p, x, j, m + 1, r);
        }
        pull(i, j);
    }

    T query(int u, int v, int i, int l, int r) {
        if (v < l || r < u) return __m_Id;
        if (u <= l && r <= v) return tree[i];

        int m = midof(l, r);
        int j = rnode(i, l, r);
        return op(
            query(u, v, i + 1, l, m),
            query(u, v, j, m + 1, r)
        );
    }

    Segtree() : n(0) {}
    Segtree(int _n) : n(_n), tree(2 * _n, __m_Id) {}

    void update(int p, const T& x) {
        update(p, x, 0, 0, n - 1);
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, n - 1);
    }
};

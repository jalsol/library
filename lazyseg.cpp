#include <vector>

template <class T> struct LazySeg {
    // TODO: modify these
    static constexpr int __m_Id = 0;
    T op(const T& x, const T& y) {
        return x + y;
    }
    void push(int i, int l, int r) {
        if (lazy[i] == 0) return;

        tree[i] += T(r - l + 1) * lazy[i];
        if (l < r) {
            for (int x : { i + 1, rnode(i, l, r) }) {
                lazy[x] += lazy[i];
            }
        }

        lazy[i] = 0;
    }

    int n;
    std::vector<T> tree, lazy;

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

    void update(int u, int v, T x, int i, int l, int r) {
        push(i, l, r);
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            lazy[i] += x;
            push(i, l, r);
            return;
        }
        int m = midof(l, r);
        int j = rnode(i, l, r);
        update(u, v, x, i + 1, l, m);
        update(u, v, x, j, m + 1, r);
        pull(i, j);
    }

    T query(int u, int v, int i, int l, int r) {
        push(i, l, r);
        if (v < l || r < u) return __m_Id;
        if (u <= l && r <= v) return tree[i];

        int m = midof(l, r);
        int j = rnode(i, l, r);
        return op(
            query(u, v, i + 1, l, m),
            query(u, v, j, m + 1, r)
        );
    }

    LazySeg() : n(0) {}
    LazySeg(int _n) : n(_n), tree(2 * _n, __m_Id), lazy(2 * _n) {}

    void update(int l, int r, T x) {
        update(l, r, x, 0, 0, n - 1);
    }
    T query(int l, int r) {
        return query(l, r, 0, 0, n - 1);
    }
};


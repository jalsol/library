template <class T> struct Segtree {
    // supports range query point update
    // DEFAULT: operator+()
private:
    // TODO: modify this
    static constexpr int __m_Id = 0;

    int n;
    std::vector<T> tree, lazy;
 
    int __mid_range(int l, int r) {
        assert(l <= r);
        return l + (r - l) / 2;
    }
 
    int __right_node(int i, int l, int r) {
        int m = __mid_range(l, r);
        return i + (m - l + 1) * 2;
    }
 
    // TODO: modify this
    T __op(T x, T y) {
        return x + y;
    }
 
    void __pull(int i, int j) {
        tree[i] = __op(tree[i + 1], tree[j]);
    }
 
    void __update(int p, T x, int i, int l, int r) {
        if (p < l || r < p) return;

        if (l == r) {
            tree[i] = x;
            return;
        }

        int m = __mid_range(l, r);
        int j = __right_node(i, l, r);

        if (p <= m) {
            __update(p, x, i + 1, l, m);
        }
        else {
            __update(p, x, j, m + 1, r);
        }

        __pull(i, j);
    }
 
    T __query(int u, int v, int i, int l, int r) {
        if (v < l || r < u) return __m_Id;
        if (u <= l && r <= v) return tree[i];
 
        int m = __mid_range(l, r);
        int j = __right_node(i, l, r);
        T left = __query(u, v, i + 1, l, m);
        T right = __query(u, v, j, m + 1, r);
        return __op(left, right);
    }
 
public:
    Segtree(int _n)
        : n(_n),
          tree(2 * _n + 5, __m_Id),
          lazy(2 * _n + 5) {}
 
    void update(int p, T x) {
        __update(p, x, 0, 0, n - 1);
    }

    T query(int l, int r) {
        return __query(l, r, 0, 0, n - 1);
    }
};

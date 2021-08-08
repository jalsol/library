template <int __Mod> struct Modint {
    int v;
    explicit operator int() const { return v; }

    Modint() : v(0) {}
    Modint(long long _v) : v(_v % __Mod) { v += __Mod * (v < 0); }

    friend std::ostream& operator<<(std::ostream& os, const Modint& a) { return os << int(a); }
    friend std::istream& operator>>(std::istream& is, Modint& a) { long long x; is >> x; a = Modint(x); return is; }

    friend bool operator==(const Modint& a, const Modint& b) { return a.v == b.v; }
    friend bool operator!=(const Modint& a, const Modint& b) { return a.v != b.v; }

    static int inv_mod(int a, int m = __Mod) { int g = m, r = a, x = 0, y = 1; while (r != 0) { int q = g / r; g %= r; std::swap(g, r); x -= q * y; std::swap(x, y); } return x < 0 ? x + m : x; }
    Modint power(long long p) const { if (p < 0) return inv().power(-p); Modint a = *this, ret = 1; for (; p; p >>= 1, a *= a) if (p & 1) ret *= a; return ret; }

    Modint inv() const { return inv_mod(v); }
    friend Modint inv(const Modint& a) { return a.inv(); }

    Modint neg() const { Modint ret; ret.v = v ? __Mod - v : 0; return ret; }
    friend Modint neg(const Modint& a) { return a.neg(); }

    Modint operator+() const { return Modint(*this); }
    Modint operator-() const { return neg(); }

    Modint operator++() { if (++v == __Mod) v = 0; return *this; }
    Modint operator--() { if (v == 0) v = __Mod; --v; return *this; }

    Modint& operator+=(const Modint& a) { v -= __Mod - a.v; v = (v < 0) ? v + __Mod : v; return *this; }
    Modint& operator-=(const Modint& a) { v -= a.v; v = (v < 0) ? v + __Mod : v; return *this; }
    Modint& operator*=(const Modint& a) { return *this = Modint(1LL * v * a.v); } // subject to change
    Modint& operator/=(const Modint& a) { return *this *= a.inv(); }

    friend Modint operator++(Modint& a, int) { Modint r = a; ++a; return r; }
    friend Modint operator--(Modint& a, int) { Modint r = a; --a; return r; }
    friend Modint operator+(const Modint& a, const Modint& b) { return Modint(a) += b; }
    friend Modint operator-(const Modint& a, const Modint& b) { return Modint(a) -= b; }
    friend Modint operator*(const Modint& a, const Modint& b) { return Modint(a) *= b; }
    friend Modint operator/(const Modint& a, const Modint& b) { return Modint(a) /= b; }
};

using mint = Modint<1000000000 + 7>;

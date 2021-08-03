struct mint {
    int v;
    static const int mod = 1e9 + 7;
    explicit operator int() const { return v; }

    mint() : v(0) {}
    mint(long long _v) : v(_v % mod) { v += mod * (v < 0); }

    friend std::ostream& operator<<(std::ostream& os, const mint& a) { return os << int(a); }
    friend std::istream& operator>>(std::istream& is, mint& a) { long long x; is >> x; a = mint(x); return is; }

    friend bool operator==(const mint& a, const mint& b) { return a.v == b.v; }
    friend bool operator!=(const mint& a, const mint& b) { return a.v != b.v; }

    static int inv_mod(int a, int m = mod) { int g = m, r = a, x = 0, y = 1; while (r != 0) { int q = g / r; g %= r; std::swap(g, r); x -= q * y; std::swap(x, y); } return x < 0 ? x + m : x; }
    mint power(long long p) const { if (p < 0) return inv().power(-p); mint a = *this, ret = 1; for (; p; p >>= 1, a *= a) if (p & 1) ret *= a; return ret; }

    mint inv() const { return inv_mod(v); }
    friend mint inv(const mint& a) { return a.inv(); }

    mint neg() const { mint ret; ret.v = v ? mod - v : 0; return ret; }
    friend mint neg(const mint& a) { return a.neg(); }

    mint operator+() const { return mint(*this); }
    mint operator-() const { return neg(); }

    mint operator++() { if (++v == mod) v = 0; return *this; }
    mint operator--() { if (v == 0) v = mod; --v; return *this; }

    mint& operator+=(const mint& a) { v -= mod - a.v; v = (v < 0) ? v + mod : v; return *this; }
    mint& operator-=(const mint& a) { v -= a.v; v = (v < 0) ? v + mod : v; return *this; }
    mint& operator*=(const mint& a) { return *this = mint(1LL * v * a.v); } // subject to change
    mint& operator/=(const mint& a) { return *this *= a.inv(); }

    friend mint operator++(mint& a, int) { mint r = a; ++a; return r; }
    friend mint operator--(mint& a, int) { mint r = a; --a; return r; }
    friend mint operator+(const mint& a, const mint& b) { return mint(a) += b; }
    friend mint operator-(const mint& a, const mint& b) { return mint(a) -= b; }
    friend mint operator*(const mint& a, const mint& b) { return mint(a) *= b; }
    friend mint operator/(const mint& a, const mint& b) { return mint(a) /= b; }
};


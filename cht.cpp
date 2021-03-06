#include <set>
#include <climits>

using namespace std;

using ll = long long;

bool Q;

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const {
        return Q ? p < o.p : k < o.k;
    }
};

struct Hull : multiset<Line> {
    static constexpr ll inf = LLONG_MAX;

    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = inf;
            return false;
        }

        if (x->k == y->k) {
            x->p = (x->m > y->m) ? inf : -inf;
        } else {
            x->p = div(y->m - x->m, x->k - y->k);
        }

        return x->p >= y->p;
    }

    void add(ll k, ll m) {
        auto z = insert({k, m, 0});
        auto y = z++;
        auto x = y;

        while (isect(y, z)) z = erase(z);

        if (x != begin() && isect(--x, y)) {
            isect(x, y = erase(y));
        }

        while ((y = x) != begin() && (--x)->p >= y->p) {
            isect(x, erase(y));
        }
    }

    ll query(ll x) {
        Q = true;
        auto it = lower_bound({0, 0, x});
        Q = false;
        return it->k * x + it->m;
    }
};

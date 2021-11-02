#include <functional>
#include <set>

constexpr long long CHTQuery = -(1LL << 62);

struct Line {
    long long a, b;
    mutable std::function<const Line*()> getNxt;

    Line(long long _a, long long _b) : a(_a), b(_b) {}

    bool operator<(const Line& o) const {
        if (o.b != CHTQuery) return a < o.a;

        const Line* nxt = getNxt();
        if (nxt == nullptr) return false;

        return b - nxt->b < (nxt->a - a) * o.a;
    }
};

struct CHT : public std::multiset<Line> {
    bool bad(iterator it) {
        if (size() == 1) return false;

        auto right = next(it);
        if (it == begin()) {
            return (it->a == right->a) && (it->b <= right->b);
        }

        auto left = prev(it);
        if (right == end()) {
            return (it->a == left->a) && (it->b <= left->b);
        }

        return (left->b - it->b) * (right->a - it->a) >= (it->b - right->b) * (it->a - left->a);
    }

    void add(long long a, long long b) {
        auto it = insert({ a, b });

        if (bad(it)) {
            erase(it);
            return;
        }

        while (next(it) != end() && bad(next(it))) {
            erase(next(it));
        }

        it->getNxt = [=] { return next(it) == end() ? nullptr : &*next(it); };

        while (it != begin() && bad(prev(it))) {
            erase(prev(it));
        }

        if (it != begin()) {
            prev(it)->getNxt = [=] { return &*it; };
        }
    }

    long long query(long long x) {
        auto l = *lower_bound(Line(x, CHTQuery));
        return l.a * x + l.b;
    }
};


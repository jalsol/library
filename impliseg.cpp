#include <vector>
#include <cassert>

static char buf[450 << 20];
void* operator new (size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void*)&buf[i -= s];
}
void operator delete (void*) {}

struct Node {
    static constexpr int inf = 1e9;
    Node* l = 0;
    Node* r = 0;
    int lo, hi, mset = inf, madd = 0, val = -inf;

    Node(int lo, int hi): lo(lo), hi(hi) {}

    Node(const std::vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
        if (!(lo + 1 < hi)) {
            val = v[lo];
            return;
        }

        int mid = lo + (hi - lo) / 2;
        l = new Node(v, lo, mid); r = new Node(v, mid, hi);
        val = std::max(l->val, r->val);
    }

    int query(int L, int R) {
        if (R <= lo || hi <= L) return -inf;
        if (L <= lo && hi <= R) return val;
        push();
        return std::max(l->query(L, R), r->query(L, R));
    }

    void set(int L, int R, int x) {
        if (R <= lo || hi <= L) return;

        if (L <= lo && hi <= R) {
            mset = val = x, madd = 0;
            return;
        }

        push(), l->set(L, R, x), r->set(L, R, x);
        val = std::max(l->val, r->val);
    }

    void add(int L, int R, int x) {
        if (R <= lo || hi <= L) return;

        if (L <= lo && hi <= R) {
            if (mset != inf) mset += x;
            else madd += x;
            val += x;
            return;
        }

        push(), l->add(L, R, x), r->add(L, R, x);
        val = std::max(l->val, r->val);
    }

    void push() {
        if (!l) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid); r = new Node(mid, hi);
        }
        if (mset != inf) {
            l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
        }
        else if (madd) {
            l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
        }
    }
};

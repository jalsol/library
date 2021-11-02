#include <vector>
#include <cassert>

template<class T>
struct RMQ {
    std::vector<std::vector<T>> jmp;

    RMQ(const std::vector<T>& v) : jmp(1, v) {
        for (int pw = 1, k = 1; pw * 2 <= int(v.size()); pw *= 2, ++k) {
            jmp.emplace_back(int(v.size()) - pw * 2 + 1);

            for (int j = 0; j < jmp[k].size(); ++j) {
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
        }
    }

    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

#include <iostream>
#include <vector>

std::vector<int> Z(std::string s) {
    int n = s.size();
    std::vector<int> z(n); z[0] = n;

    int l = 1, r = 0;

    for (int i = 1; i < n; i++) {
        if (l <= r) {
            z[i] = std::min(z[i - l], r - i + 1);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

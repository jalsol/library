#include <bits/stdc++.h>

std::vector<int> Z(const std::string& s) {
    int l = -1, r = -1, n = s.size();
    std::vector<int> z(n);
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = std::min(r - i, z[i - l]);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// Reference:
// D. Gusfield,
// Algorithms on Strings, Trees, and Sequences: Computer Science and
// Computational Biology
template <class T> std::vector<int> z_algorithm(const std::vector<T>& s) {
    int n = int(s.size());
    if (n == 0) return {};
    std::vector<int> z(n);
    z[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        int& k = z[i];
        // j + z[j] - i : i be start point max match length -> (r-i+1)
        // z[i-j] : the shadow point lenth
        // (l, r) -> [j, j + z[j])
        k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);
        while (i + k < n && s[k] == s[i + k]) k++;
        if (j + z[j] < i + z[i]) j = i;
    }
    z[0] = n;
    return z;
}

std::vector<int> z_algorithm(const std::string& s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return z_algorithm(s2);
}

std::vector<int> ex_KMP(const std::string& s, const std::string& t) {
    int n = int(s.size()), m = int(t.size());
    std:vector<int> z = z_algorithm(t);
    
    std::vector<int> extend(n);
    int r = 0;
    while (r < n && r < m && s[r] == t[r]) r++; // init
    extend[0] = r;
    for (int i = 1, j = 0; i < n; i++) {
        int &k = extend[i];
        k = (j + extend[j] <= i)? 0 : std::min(j + extend[j] - i, z[i-j]);
        while (i + k < n && k < m && s[i + k] == t[k]) k++;
        if (j + extend[j] < i + extend[i]) j = i;
    }
    //
    //    for (int i = 1, j = 0; i < n; i++) {
    //        r = j + extend[j] - 1;
    //        int len = z[i - j];
    //        if (i + len <= r) extend[i] = len;
    //        else {
    //            int tmp = max(0, r - i + 1);
    //            while (i + tmp < n && tmp < m && s[i + tmp] == t[tmp]) tmp++;
    //            extend[i] = tmp;
    //            j = i;
    //        }
    //    }
    return extend;
}


vector<int> preKMP(string &pattern) {
    int n = int(pattern.size());
    vector<int> pmt(n, 0);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && pattern[i] != pattern[j]) {
            j = pmt[j - 1];
        }
        if (pattern[i] == pattern[j]) j++;
        pmt[i] = j;
    }
    return pmt;
}

vector<int> KMP(string &origin, string &pattern) {
    vector<int> pmt = preKMP(pattern);
    int n = int(origin.size()), m = int(pattern.size());
    vector<int> place;
    for (int i = 0, j = 0; i < n; i++) {
        while (j && origin[i] != pattern[j]) {
            j = pmt[j - 1];
        }
        if (origin[i] == pattern[j]) j++;
        if (j == m) {
            place.emplace_back(i - j + 1);
        }
    }
    return place; // return all match start point
}


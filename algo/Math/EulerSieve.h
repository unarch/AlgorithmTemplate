vector<int> init(int n) {
    vector<int> primes;
    vector<bool> vis(n + 1, false);
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            primes.push_back(i);
        }
        for (auto x : primes) {
            if (i * x > n) {
                break;
            }
            vis[i * x] = true;
            // x is min prime for i * x
            if (i % x == 0) {
                break;
            }
        }
    }
    return primes;
}


class HashString {
private:
    struct HashSeq {
        vector<long long> P, H;
        int MOD, BASE;
        
        HashSeq() {}
        
        HashSeq(string &s, int MOD, int BASE): MOD(MOD), BASE(BASE) {
            int n = int(s.size());
            P.resize(n + 1);
            P[0] = 1;
            for (int i = 1; i <= n; i++) P[i] = P[i - 1] * BASE % MOD;
            H.resize(n + 1);
            H[0] = 0;
            for (int i = 1; i <= n; i++) H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;
        }
        
        long long query(int l, int r) {
            // H[r] = ax^4 + bx^3 + cx^2 + dx^1 + e
            // target -> cde -> cx^6 + dx^5 + ex^4
            // H[l - 1] = ax^1 + bx
            // p[r - l + ] = x^3
            // -> p[r - l + 1] * H[l-1] = ax^4 + bx^3
            // H[r] - ax^4 + bx^3 = cx^2 + dx
            return (H[r] - H[l - 1] * P[r - l + 1] % MOD + MOD) % MOD;
        }
    };
    
    
    HashSeq hs1, hs2;
    int MOD1, BASE1;
    int MOD2, BASE2;
public:
    HashString(string &s) {
        mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
        
        auto rnd = [&](int x, int y) {
            return uniform_int_distribution<int>(x, y)(rng);
        };
        
        MOD1 = 998244353 + rnd(0, 1e9);BASE1 = 233 + rnd(0, 1e3);
        MOD2 = 998244353 + rnd(0, 1e9);BASE2 = 233 + rnd(0, 1e3);
        hs1 = HashSeq(s, MOD1, BASE1);
        hs2 = HashSeq(s, MOD2, BASE2);
    }
    
    long long query(int l, int r) {
        return hs1.query(l, r) * MOD1 + hs2.query(l, r);
    }
};


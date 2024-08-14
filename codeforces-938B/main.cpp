#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <random>
#include <chrono>
#include <iomanip>
#include <time.h>
#include <climits>

using namespace std;

#ifdef LOCAL
#include "../algo/debug.h"
#else
#define debug(...) 42
#endif
 
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n';
using i64 = long long;
using i64 = long long;
using u64 = unsigned long long;

typedef pair<int,int> pii;
typedef pair<i64, i64> pll;
typedef pair<int, i64> pil;
typedef vector<vector<int> > vvi;
const i64 mod = 1e9 + 7;
const int maxn = 1e5 + 50;
const int inf = 1e9;
template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    int __lg(int __n) {
        int __k = 0;
        for (__k = 0; __n != 0; __n >>= 1) ++__k;
        return __k - 1;
    }
    
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        auto build = [&](auto &&self, int p, int l, int r) -> void {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
            pull(p);
        };
        build(build, 1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    int max = 0;
};

Info operator+(const Info &a, const Info &b) {
    return {
        std::max(a.max, b.max)
    };
}

int N = 2000000 + 100;
SegmentTree tree(N, Info{});

void solve() {
    
    int n;
    cin >> n;
    
    tree.modify(1, {N});
    tree.modify(N - 1, {N});
    set<int> s{0, 2 * N};
    
    auto insert = [&](int x) {
        auto rt = s.insert(x).first;
        auto l = *prev(rt);
        auto r = *next(rt);
        tree.modify(l + 1, {x - l - 1});
        tree.modify(x + 1, {r - x - 1});
    };
    
    auto erase = [&](int x) {
        auto rt = s.find(x);
        auto l = *prev(rt);
        auto r = *next(rt);
        tree.modify(l + 1, {r - l - 1});
        tree.modify(*rt + 1, {0});
        s.erase(rt);
    };
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        insert(x);
    }
    int m;
    cin >> m;
    while (m--) {
        char op;
        int x, k;
        cin >> op;
        if (op == '+') {
            cin >> x;
            insert(x);
        }
        if (op == '-') {
            cin >> x;
            erase(x);
        }
        if (op == '?') {
            cin >> k;
            auto idx = tree.findFirst(1, N, [&](const Info &s){
                return s.max >= k;
            });
            cout << idx << " ";
        }
    }
    cout << endl;
    for (auto x : s) {
        if (x < N) {
            tree.modify(x + 1, {});
        }
    }
    
    
    
}

int main(int argc, const char * argv[]) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int Time=(int)clock();
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    int t = 1;
    cin >> t;
    
    while (t--) {
        solve();
    }
    look_time
    return 0;
}




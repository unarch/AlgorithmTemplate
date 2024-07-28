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
typedef pair<i64, int> pli;
typedef vector<vector<int> > vvi;
const i64 mod = 1e9 + 7;
const int maxn = 1e5 + 50;

const i64 inf = 1e9;
const i64 cannot = 1e18;
template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazySegmentTree(std::vector<T> init_) {
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
        tag.assign(4 << __lg(n), Tag());
        auto build = [&](auto &&self, int p, int l, int r) -> void {
            debug(make_tuple(p, l, r));
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
    void print() {
        auto pr = [&](auto &&self,int p, int l, int r) {
            if (r - l == 1) {
                debug(make_pair(make_tuple(p, l, r),make_pair(info[p].min, tag[p].x)));
                return;
            }
            int m = (l + r) / 2;
            push(p);
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m, r);
            pull(p);
            debug(make_pair(make_tuple(p, l, r),make_pair(info[p].min, tag[p].x)));
        };
        pr(pr, 1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
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
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        debug(make_tuple(p, l, r));
        
        if (l >= y || r <= x) {
            debug("return");
            return;
        }
        if (l >= x && r <= y) {
            debug("apply");
            apply(p, v);
            debug(make_tuple(p,info[p].min, tag[p].x));
            return;
        }
        int m = (l + r) / 2;
        debug(make_tuple(p,info[p].min, tag[p].x));
        push(p);
        
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
        debug(make_tuple(make_tuple(p, l, r), info[p].min, tag[p].x));
        debug("\n");
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
};

struct Tag {
    i64 x = 0;
    void apply(const Tag &t) & {
        if(t.x == 0) return;
        x = t.x;
    }
};

struct Info {
    i64 min = 1e18;
    void apply(const Tag &t) & {
        if(t.x == 0) return;
        min = t.x;
    }
};

Info operator+(const Info &a, const Info &b) {
    Info nw = Info();
    nw.min = min(a.min, b.min);
    return nw;
}



void solve() {
    int n, q;
    cin >> n >> q;
    vector<tuple<i64, int, int>> Q(q);
    for (int i = 0; i < q; i++) {
        int l, r; i64 c;
        cin >> l >> r >> c;
        Q[i] = make_tuple(c, l, r);
    }
    sort(Q.begin(), Q.end());
    LazySegmentTree<Info, Tag> tree(n - 1, {-1});
    
    debug(Q);
    i64 ans = 0;
    for (int i = q - 1; i >= 0; i--) {
        debug(i);
        auto [c, l, r] = Q[i];
        l--;r--;
        debug(make_tuple(l, r, c));
        ans += c;
        tree.rangeApply(l, r, Tag {c} );
    }
    
    Info root = tree.rangeQuery(0, n);
    if (root.min == -1) {
        cout << -1 << endl;
        return;
    }
    
    tree.print();
    for (int i = 0; i < n - 1; i++) {
        Info val = tree.rangeQuery(i, i + 1);
        debug(make_tuple(i, i + 1, val.min));
        ans += val.min;
    }
    
    cout << ans << endl;
    
    
}

int main(int argc, const char * argv[]) {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    int Time=(int)clock();
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    int t = 1;
//    cin >> t;
    
    while (t--) {
        solve();
    }
    look_time
    return 0;
}




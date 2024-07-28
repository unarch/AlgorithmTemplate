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



void solve() {
    
    int n, k;
    cin >> n >> k;
    
    vector<i64> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    i64 l = 1, r = 1e9, target = 1;
    while (l <= r) {
        i64 mid = (l + r) / 2;
        i64 cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] >= mid) {
                cnt += (a[i] - mid) / b[i] + 1;
            }
        }
        if (cnt >= k) {
            target = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    debug(l);
    debug(r);
    debug(target);
    i64 ans = 0, remain = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= target) {
            i64 cnt = (a[i] - target) / b[i] + 1;
            debug(make_pair(i, cnt));
            remain += cnt;
            i64 tmp = a[i] * cnt + (cnt - 1) * cnt / 2LL * (- b[i]);
            debug(make_pair(i, tmp));
            ans += tmp;
        }
    }
    debug(remain);
    debug(k);
    ans -= (max(0LL, remain - k)) * target;
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
    cin >> t;
    
    while (t--) {
        solve();
    }
    look_time
    return 0;
}




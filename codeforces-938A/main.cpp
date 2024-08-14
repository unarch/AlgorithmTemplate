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
const int maxn = 1e6 + 50;
const int inf = 1e8;

void solve() {
    
    int n, m;
    cin >> n >> m;
    int t1, t2, t0;
    cin >> t0 >> t1 >> t2;
    
    vector<vector<array<int, 3>>> G(n);
    for (int i = 0; i < m; i++) {
        int u, v, l1, l2;
        cin >> u >> v >> l1 >> l2;
        u--;
        v--;
        G[u].push_back({v, l1, l2});
        G[v].push_back({u, l1, l2});
    }
    priority_queue<pair<int, int>> pq;
    pq.push({t0, n - 1});
    vector<int> dp(n, -1);
    
    while (!pq.empty()) {
        auto [t, u] = pq.top();
        pq.pop();
        if (dp[u] != -1) {
            continue;
        }
        dp[u] = t;
        debug(G[u]);
        for (auto [v, l1, l2] : G[u]) {
            int next = -1;
            next = max(next, t - l2);
            if (t - l1 >= t2) {
                next = max(next, t - l1);
            }
            next = max(next, min(t, t1) - l1);
            pq.push({next, v});
        }
    }
    
    cout << dp[0] << endl;
    
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




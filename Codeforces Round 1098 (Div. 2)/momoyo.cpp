#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void x() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n + 1);
    long long t = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        t += a[i];
    }
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<long long> s(n + 1, 0);
    vector<vector<int>> d(n + 1);
    auto b = [&](auto& self, int u, int p) -> void {
        s[u] = a[u];
        for (int v : g[u]) {
            if (v != p) {
                d[u].push_back(v);
                self(self, v, u);
                s[u] += s[v];
            }
        }
        sort(d[u].begin(), d[u].end(), [&](int y, int z) {
            return s[y] < s[z];
        });
    };
    b(b, 1, 0);

    auto c = [&](long long X) -> bool {
        int m = 0;
        if (t >= X) m = 0;
        else return false;

        vector<int> f(n + 1, -1);
        auto e = [&](auto& self, int u) -> void {
            int q = 0;
            for (int v : d[u]) {
                self(self, v);
                if (f[v] != -1) q++;
            }
            f[u] = (s[u] >= X) ? 0 : -1;

            vector<pair<long long, int>> C;
            C.reserve(q);
            for (int v : d[u]) {
                if (f[v] != -1) {
                    if (s[u] - s[v] >= X) {
                        f[u] = max(f[u], f[v] + 1);
                    }
                    C.push_back({s[v], f[v]});
                }
            }

            for (auto& p : C) {
                if (t - p.first >= X) {
                    m = max(m, p.second + 1);
                }
            }

            int M = C.size();
            if (M >= 2) {
                vector<int> P(M);
                P[0] = C[0].second;
                for (int i = 1; i < M; ++i) {
                    P[i] = max(P[i - 1], C[i].second);
                }
                long long W = t - X;
                for (int j = 1; j < M; ++j) {
                    long long r = W - C[j].first;
                    if (r < C[0].first) break;

                    int l = 0, h = j - 1, R = -1;
                    while (l <= h) {
                        int mid = l + (h - l) / 2;
                        if (C[mid].first <= r) {
                            R = mid;
                            l = mid + 1;
                        } else {
                            h = mid - 1;
                        }
                    }
                    if (R != -1) {
                        m = max(m, C[j].second + P[R] + 2);
                    }
                }
            }
        };
        e(e, 1);
        return m >= k;
    };

    long long l = 1, r = t, ans = -1;
    while (l <= r) {
        long long mid = l + (r - l) / 2;
        if (c(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (ans == -1) cout << -1 << "\n";
    else cout << (ans % 10) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) x();
    return 0;
}

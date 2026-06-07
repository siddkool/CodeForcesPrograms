#include <iostream>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;
const int maxn = 500005;

long long fct[maxn];
bool pos;
long long prd;
vector<long long> a;

long long pwr(long long b, long long e) {
    long long r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % mod;
        b = b * b % mod;
        e /= 2;
    }
    return r;
}

long long inv(long long n) {
    return pwr(n, mod - 2);
}

void init() {
    fct[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        fct[i] = fct[i - 1] * i % mod;
    }
}

void rec(int l, int r) {
    if (l > r || !pos) return;
    long long len = r - l + 1;
    prd = prd * len % mod;
    int fnd = -1;
    for (int d = 0; d <= len / 2; ++d) {
        int m1 = l + d;
        if (a[m1] == 1LL * (m1 - l + 1) * (r - m1 + 1)) {
            fnd = m1;
            break;
        }
        int m2 = r - d;
        if (a[m2] == 1LL * (m2 - l + 1) * (r - m2 + 1)) {
            fnd = m2;
            break;
        }
    }
    if (fnd == -1) {
        pos = false;
        return;
    }
    rec(l, fnd - 1);
    rec(fnd + 1, r);
}

void solve() {
    int t;
    if (!(cin >> t)) return;
    while (t--) {
        int n;
        cin >> n;
        a.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        pos = true;
        prd = 1;
        rec(1, n);
        if (!pos) {
            cout << 0 << "\n";
        } else {
            long long ans = fct[n] * inv(prd) % mod;
            cout << ans << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    solve();
    return 0;
}

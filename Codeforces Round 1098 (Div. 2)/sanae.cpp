#include <iostream>

using namespace std;

const int M = 2000005;
int a[M], b[M], c[M], d[M], e[M], f[M], g[M], h[M], v[M];

void w() {
    int n;
    cin >> n;
    for (int i = 0; i <= n + 1; ++i) {
        a[i] = n + 1;
        b[i] = 0;
        c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        if (y < a[x]) a[x] = y;
        if (y > b[x]) b[x] = y;
        c[y] = 1;
    }
    d[0] = 0;
    for (int i = 1; i <= n; ++i) {
        d[i] = d[i - 1] + c[i];
    }
    int p = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] <= n) {
            v[p++] = i;
        }
    }
    if (p == 0) {
        cout << 0 << "\n";
        return;
    }
    e[0] = a[v[0]];
    f[0] = b[v[0]];
    for (int i = 1; i < p; ++i) {
        e[i] = e[i - 1] < a[v[i]] ? e[i - 1] : a[v[i]];
        f[i] = f[i - 1] > b[v[i]] ? f[i - 1] : b[v[i]];
    }
    g[p - 1] = a[v[p - 1]];
    h[p - 1] = b[v[p - 1]];
    for (int i = p - 2; i >= 0; --i) {
        g[i] = g[i + 1] < a[v[i]] ? g[i + 1] : a[v[i]];
        h[i] = h[i + 1] > b[v[i]] ? h[i + 1] : b[v[i]];
    }
    long long s = 0;
    for (int i = 0; i < p - 1; ++i) {
        int l = e[i] > g[i + 1] ? e[i] : g[i + 1];
        int r = f[i] < h[i + 1] ? f[i] : h[i + 1];
        if (l < r) {
            s += d[r - 1] - d[l - 1];
        }
    }
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    if (cin >> t) {
        while (t--) {
            w();
        }
    }
    return 0;
}

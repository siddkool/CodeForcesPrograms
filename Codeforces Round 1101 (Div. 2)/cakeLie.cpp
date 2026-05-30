#include <bits/stdc++.h>
using namespace std;

long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long d = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

long long modinv(long long n, long long m) {
    if (m == 1) return 0;
    long long x, y;
    extgcd(n, m, x, y);
    return (x % m + m) % m;
}

int evaluate(long long t, int m, long long a, long long b, long long k, long long xm, long long am) {
    long long curr;
    if (am > 0 && t > (2000000000000000000LL - xm) / am) curr = k + 1;
    else curr = xm + t * am;

    for(int j = 0; j <= m; ++j) {
        if (curr < 0) return (j % 2 == 0) ? -1 : 1;
        if (j == m) break;
        if (curr > k) curr = -1;
        else curr = (k - b * curr) / a;
    }
    return 0;
}

void solve() {
    long long n, a, b, k;
    cin >> n >> a >> b >> k;

    long long g = std::gcd(a, b);
    if (k % g != 0) {
        long long perfectCookCake = 0;
        cout << perfectCookCake << "\n";
        return;
    }

    a /= g; b /= g; k /= g;

    if (a == b) {
        long long perfectCookCake = n;
        cout << perfectCookCake << "\n";
        return;
    }

    long long len = 0;
    long long curr = 0;
    while (true) {
        if (curr * b > k) break;
        long long rem = k - curr * b;
        if (rem % a != 0) break;
        curr = rem / a;
        len++;
    }

    if (n <= len) {
        long long perfectCookCake = n;
        cout << perfectCookCake << "\n";
        return;
    }

    if (k % (a + b) == 0) {
        long long perfectCookCake = len + n - len - 1;
        cout << perfectCookCake << "\n";
        return;
    }

    long long longest = 0;
    long long x = 0;
    long long apow = 1;
    long long binv = modinv(b % a, a);
    long long pmod = 1;

    for (int m = 1; m <= 40; ++m) {
        if (m == 1) {
            x = ((k % a) * binv) % a;
            apow = a;
        } else {
            long long y = x;
            for(int j = 0; j < m - 1; ++j) {
                y = (k - b * y) / a;
            }
            long long rem = (k - b * y) % a;
            if (rem < 0) rem += a;

            pmod = (pmod * ((-b) % a + a)) % a;
            long long inv = modinv((b * pmod) % a, a);
            long long tval = (rem * inv) % a;

            long long nextpow = (apow > 2000000000000000000LL / a) ? 2000000000000000000LL : apow * a;
            long long add_val = (tval > 0 && apow > 2000000000000000000LL / tval) ? 2000000000000000000LL : tval * apow;

            x = (x > 2000000000000000000LL - add_val) ? 2000000000000000000LL : x + add_val;
            apow = nextpow;
        }

        if (x > k / b) break;

        long long count = 0;
        if (apow > k / b) {
            if (evaluate(0, m, a, b, k, x, apow) == 0) count = 1;
        } else {
            long long maxt = (k / b - x) / apow;
            long long lt = 0, rt = maxt, bl = maxt + 1;
            while (lt <= rt) {
                long long mid = lt + (rt - lt) / 2;
                int res = evaluate(mid, m, a, b, k, x, apow);
                if (res == -1) lt = mid + 1;
                else { bl = mid; rt = mid - 1; }
            }
            lt = 0; rt = maxt;
            long long br = -1;
            while (lt <= rt) {
                long long mid = lt + (rt - lt) / 2;
                int res = evaluate(mid, m, a, b, k, x, apow);
                if (res == 1) rt = mid - 1;
                else { br = mid; lt = mid + 1; }
            }
            if (bl <= br) count = br - bl + 1;
        }
        if (count > 0) longest = m;
        else break;
    }

    long long rem = n - len;
    long long perfectCookCake = len;
    if (longest > 0) {
        perfectCookCake += (rem / (longest + 1)) * longest + max(0LL, rem % (longest + 1) - 1);
    }
    cout << perfectCookCake << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}

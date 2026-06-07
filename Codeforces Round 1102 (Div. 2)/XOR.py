#include <iostream>
#include <string>

using namespace std;

void solve() {
    int t;
    if (!(cin >> t)) return;

    while (t--) {
        long long n, k;
        cin >> n >> k;
        string s, z;
        cin >> s >> z;

        long long a = 2;
        long long b = 2;

        for (int i = 0; i < k - 1; ++i) {
            long long c = a + b - 1;
            long long d = a * 2;
            a = c;
            b = d;
        }

        long long arr[4] = {0, a, a, b};
        long long freq[4] = {0, 0, 0, 0};

        for (int i = 0; i < n; ++i) {
            int u = s[i] - '0';
            int v = z[i] - '0';
            freq[(u << 1) | v]++;
        }

        long long ans = 0;

        for (int i = 0; i < 4; ++i) {
            if (!freq[i]) continue;
            for (int j = 0; j < 4; ++j) {
                if (!freq[j]) continue;
                int u = (i >> 1) ^ (j >> 1);
                int v = (i & 1) ^ (j & 1);
                ans += freq[i] * freq[j] * arr[(u << 1) | v];
            }
        }

        cout << ans / 2 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int t;
    if (!(cin >> t)) return;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }

//j
        vector<long long> H(2 * n);
        for (int i = 0; i < 2 * n; ++i) {
            H[i] = h[i % n];
        }

        vector<long long> L(n, 0), R(n, 0);
        for (int j = 0; j < n; ++j) {
            long long m1 = 0;
            for (int k = 1; k < n; ++k) {
                if (H[j + k - 1] > m1) m1 = H[j + k - 1];
                L[k] = m1;
            }

            long long m2 = 0;
            for (int k = n - 1; k >= 0; --k) {
                if (H[j + k] > m2) m2 = H[j + k];
                R[k] = m2;
            }

            long long tot = 0;
            for (int k = 0; k < n; ++k) {
                tot += (L[k] < R[k] ? L[k] : R[k]);
            }

            cout << tot << (j == n - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {


    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

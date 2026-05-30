#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const long long MOD = (1LL << 30) - 73741815;

long long fact[5005];

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= 5000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

struct Snake {
    int id;
    int size;
    int r, c;
    string path;
};

struct DSU {
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            size[root_j] += size[root_i];
        }
    }
};

void solve() {
    int n, k;
    if (!(cin >> n >> k)) return;

    vector<Snake> snakes(k);
    DSU dsu(n);

    for (int i = 0; i < k; i++) {
        cin >> snakes[i].size;
        snakes[i].id = (snakes[i].size + 1) / 2;
        cin >> snakes[i].r >> snakes[i].c;
        if (snakes[i].size > 1) {
            cin >> snakes[i].path;
        } else {
            snakes[i].path = "";
        }

        int curr_r = snakes[i].r;
        int curr_c = snakes[i].c;
        int diff = curr_r - curr_c;

        vector<pair<int, int>> cells;
        cells.push_back({curr_r, curr_c});
        for (char ch : snakes[i].path) {
            if (ch == 'R') curr_c++;
            else curr_r++;
            cells.push_back({curr_r, curr_c});
        }

        vector<int> touch_r;
        for (int j = 0; j < cells.size(); j++) {
            if (cells[j].first - cells[j].second == diff) {
                touch_r.push_back(cells[j].first);
            }
        }

        for (int j = 1; j < touch_r.size(); j++) {
            int start_row = touch_r[j-1] + 1;
            int end_row = touch_r[j];
            for (int r = start_row; r < end_row; r++) {
                dsu.unite(r, r + 1);
            }
        }
    }

    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        if (dsu.parent[i] == i) {
            ans = (ans * fact[dsu.size[i]]) % MOD;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

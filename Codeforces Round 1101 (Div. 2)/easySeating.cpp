#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    if (cin >> tests) {
        while (tests--) {
            int friends, tables, seats;
            cin >> friends >> tables >> seats;

            string line;
            cin >> line;

            int eia[3005];
            for(int index = 0; index <= tables; index++) eia[index] = -1;
            eia[0] = 0;

            for (char person : line) {
                int future[3005];
                for(int index = 0; index <= tables; index++) future[index] = eia[index];

                if (person == 'I' || person == 'A') {
                    for (int used = 0; used < tables; ++used) {
                        if (eia[used] != -1) {
                            if (eia[used] + 1 > future[used + 1]) {
                                future[used + 1] = eia[used] + 1;
                            }
                        }
                    }
                }

                if (person == 'E' || person == 'A') {
                    for (int used = 1; used <= tables; ++used) {
                        if (eia[used] != -1) {
                            int capacity = used * seats;
                            if (capacity > eia[used]) {
                                if (eia[used] + 1 > future[used]) {
                                    future[used] = eia[used] + 1;
                                }
                            }
                        }
                    }
                }

                for(int index = 0; index <= tables; index++) eia[index] = future[index];
            }

            int maximum = 0;
            for (int used = 0; used <= tables; ++used) {
                if (eia[used] > maximum) {
                    maximum = eia[used];
                }
            }

            cout << maximum << "\n";
        }
    }
    return 0;
}

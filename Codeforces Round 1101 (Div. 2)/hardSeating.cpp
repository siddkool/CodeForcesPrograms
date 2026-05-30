//originally submitted with --init128 but is rejected by gnu compiler


#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tests;
    if (cin >> tests) {
        while (tests--) {
            long long friends, tables, seats;
            cin >> friends >> tables >> seats;

            string line;
            cin >> line;

            long long vacant = tables;
            long long eia = 0;
            long long total = 0;
            long long swappable = 0;

            for (char person : line) {
                if (person == 'I') {
                    if (vacant > 0) {
                        vacant--;
                        eia += seats - 1;
                        total++;
                    }
                } else if (person == 'E') {
                    if (eia > 0) {
                        eia--;
                        total++;
                    } else if (swappable > 0 && vacant > 0) {
                        swappable--;
                        vacant--;
                        eia += seats - 1;
                        total++;
                    }
                } else if (person == 'A') {
                    if (eia > 0) {
                        eia--;
                        swappable++;
                        total++;
                    } else if (vacant > 0) {
                        vacant--;
                        eia += seats - 1;
                        total++;
                    }
                }
            }

            cout << total << "\n";
        }
    }
    return 0;
}

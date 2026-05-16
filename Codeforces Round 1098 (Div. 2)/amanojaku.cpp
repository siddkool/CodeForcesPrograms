#include <iostream>
#include <vector>

using namespace std;

long long modulo = 998244353;

long long power(long long base, long long exponent) {
    long long result = 1;
    base %= modulo;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % modulo;
        base = (base * base) % modulo;
        exponent /= 2;
    }
    return result;
}

long long inverse(long long number) {
    return power(number, modulo - 2);
}

long long factorials[2000005];
long long inverses[2000005];

void initialize() {
    factorials[0] = 1;
    inverses[0] = 1;
    for (long long index = 1; index <= 2000000; index++) {
        factorials[index] = (factorials[index - 1] * index) % modulo;
    }
    inverses[2000000] = inverse(factorials[2000000]);
    for (long long index = 1999999; index >= 1; index--) {
        inverses[index] = (inverses[index + 1] * (index + 1)) % modulo;
    }
}

long long combinations(long long items, long long choices) {
    if (choices < 0 || choices > items) return 0;
    return factorials[items] * inverses[choices] % modulo * inverses[items - choices] % modulo;
}

void solve() {
    long long size, queries;
    cin >> size >> queries;
    vector<long long> array(size + 1);
    for (long long index = 1; index <= size; index++) {
        cin >> array[index];
    }
    while (queries--) {
        long long operation, left, right, target;
        cin >> operation >> left >> right >> target;
        long long sum = 0;
        long long count = 0;
        for (long long index = left; index <= right; index++) {
            if (array[index] >= 0) sum += array[index];
            else count++;
        }
        long long remainder = target - sum;
        if (count == 0) {
            if (remainder != 0) {
                cout << 0 << "\n";
            } else {
                long long answer = 0;
                long long current = 0;
                for (long long index = left; index <= right; index++) {
                    if (array[index] >= 0) current = (current + array[index]) % modulo;
                    answer = (answer + current * current % modulo) % modulo;
                }
                cout << answer << "\n";
            }
            continue;
        }
        if (remainder < 0) {
            cout << 0 << "\n";
            continue;
        }
        long long ways = combinations(remainder + count - 1, count - 1);
        long long multiplier1 = 1;
        long long multiplier2 = (2 * remainder) % modulo * inverse(count) % modulo;
        long long multiplier3 = remainder * inverse(count) % modulo;
        long long multiplier4 = remainder * (remainder - 1) % modulo * inverse(count) % modulo * inverse(count + 1) % modulo;
        long long term1 = 0, term2 = 0, term3 = 0, term4 = 0;
        long long running = 0;
        long long variables = 0;
        for (long long index = left; index <= right; index++) {
            if (array[index] >= 0) running = (running + array[index]) % modulo;
            else variables++;
            term1 = (term1 + running * running % modulo) % modulo;
            term2 = (term2 + running * variables % modulo) % modulo;
            term3 = (term3 + variables) % modulo;
            term4 = (term4 + variables * (variables + 1) % modulo) % modulo;
        }
        long long answer = 0;
        answer = (answer + multiplier1 * term1 % modulo) % modulo;
        answer = (answer + multiplier2 * term2 % modulo) % modulo;
        answer = (answer + multiplier3 * term3 % modulo) % modulo;
        answer = (answer + multiplier4 * term4 % modulo) % modulo;
        answer = (answer * ways) % modulo;
        cout << answer << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    initialize();
    long long testcases;
    cin >> testcases;
    while (testcases--) {
        solve();
    }
    return 0;
}

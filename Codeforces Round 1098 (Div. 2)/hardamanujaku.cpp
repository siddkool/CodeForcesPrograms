//using a tree structure


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

long long facts[2000005];
long long invs[2000005];

void setup() {
    facts[0] = 1;
    invs[0] = 1;
    for (long long index = 1; index <= 2000000; index++) {
        facts[index] = (facts[index - 1] * index) % modulo;
    }
    invs[2000000] = inverse(facts[2000000]);
    for (long long index = 1999999; index >= 1; index--) {
        invs[index] = (invs[index + 1] * (index + 1)) % modulo;
    }
}

long long choose(long long items, long long choices) {
    if (choices < 0 || choices > items) return 0;
    return facts[items] * invs[choices] % modulo * invs[items - choices] % modulo;
}

struct item {
    long long length = 0;
    long long count = 0;
    long long sum = 0;
    long long truesum = 0;
    long long suma = 0;
    long long sumv = 0;
    long long sumaa = 0;
    long long sumav = 0;
    long long sumvvv = 0;
};

item tree[1200005];
long long values[300005];

item create(long long value) {
    item element;
    element.length = 1;
    if (value == -1) {
        element.count = 1;
        element.sum = 0;
        element.truesum = 0;
        element.suma = 0;
        element.sumv = 1;
        element.sumaa = 0;
        element.sumav = 0;
        element.sumvvv = 2;
    } else {
        long long val = value % modulo;
        element.count = 0;
        element.sum = val;
        element.truesum = value;
        element.suma = val;
        element.sumv = 0;
        element.sumaa = val * val % modulo;
        element.sumav = 0;
        element.sumvvv = 0;
    }
    return element;
}

item combine(item a, item b) {
    if (a.length == 0) return b;
    if (b.length == 0) return a;
    item c;
    c.length = a.length + b.length;
    c.count = a.count + b.count;
    c.sum = (a.sum + b.sum) % modulo;
    c.truesum = a.truesum + b.truesum;

    long long blen = b.length % modulo;
    long long acnt = a.count % modulo;
    long long asum = a.sum % modulo;

    c.suma = (a.suma + b.suma + asum * blen) % modulo;
    c.sumv = (a.sumv + b.sumv + acnt * blen) % modulo;

    long long terma = 2 * asum % modulo * b.suma % modulo;
    long long termb = asum * asum % modulo * blen % modulo;
    c.sumaa = (a.sumaa + b.sumaa + terma + termb) % modulo;

    long long termc = asum * b.sumv % modulo;
    long long termd = acnt * b.suma % modulo;
    long long terme = asum * acnt % modulo * blen % modulo;
    c.sumav = (a.sumav + b.sumav + termc + termd + terme) % modulo;

    long long termf = (acnt * acnt % modulo + acnt) % modulo * blen % modulo;
    long long termg = 2 * acnt % modulo * b.sumv % modulo;
    c.sumvvv = (a.sumvvv + b.sumvvv + termf + termg) % modulo;

    return c;
}

void build(long long node, long long left, long long right) {
    if (left == right) {
        tree[node] = create(values[left]);
        return;
    }
    long long mid = left + (right - left) / 2;
    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

void update(long long node, long long left, long long right, long long index, long long value) {
    if (left == right) {
        tree[node] = create(value);
        return;
    }
    long long mid = left + (right - left) / 2;
    if (index <= mid) {
        update(2 * node, left, mid, index, value);
    } else {
        update(2 * node + 1, mid + 1, right, index, value);
    }
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

item query(long long node, long long left, long long right, long long qleft, long long qright) {
    if (qleft <= left && right <= qright) {
        return tree[node];
    }
    long long mid = left + (right - left) / 2;
    if (qright <= mid) {
        return query(2 * node, left, mid, qleft, qright);
    }
    if (qleft > mid) {
        return query(2 * node + 1, mid + 1, right, qleft, qright);
    }
    return combine(query(2 * node, left, mid, qleft, qright), query(2 * node + 1, mid + 1, right, qleft, qright));
}

void solve() {
    long long size, queries;
    cin >> size >> queries;
    for (long long index = 1; index <= size; index++) {
        cin >> values[index];
    }
    build(1, 1, size);
    while (queries--) {
        long long operation;
        cin >> operation;
        if (operation == 1) {
            long long index, value;
            cin >> index >> value;
            update(1, 1, size, index, value);
        } else {
            long long left, right, target;
            cin >> left >> right >> target;
            item result = query(1, 1, size, left, right);
            long long remaining = target - result.truesum;
            long long kcnt = result.count;

            if (kcnt == 0) {
                if (remaining != 0) {
                    cout << 0 << "\n";
                } else {
                    cout << result.sumaa << "\n";
                }
                continue;
            }
            if (remaining < 0) {
                cout << 0 << "\n";
                continue;
            }

            long long modrem = remaining % modulo;
            long long ways = choose(remaining + kcnt - 1, kcnt - 1);
            long long multa = 1;
            long long multb = 2 * modrem % modulo * inverse(kcnt) % modulo;
            long long multc = modrem * inverse(kcnt) % modulo;
            long long multd = modrem * (modrem - 1 + modulo) % modulo * inverse(kcnt) % modulo * inverse(kcnt + 1) % modulo;

            long long answer = 0;
            answer = (answer + multa * result.sumaa % modulo) % modulo;
            answer = (answer + multb * result.sumav % modulo) % modulo;
            answer = (answer + multc * result.sumv % modulo) % modulo;
            answer = (answer + multd * result.sumvvv % modulo) % modulo;
            answer = (answer * ways) % modulo;

            cout << answer << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    setup();
    long long testcases;
    cin >> testcases;
    while (testcases--) {
        solve();
    }
    return 0;
}

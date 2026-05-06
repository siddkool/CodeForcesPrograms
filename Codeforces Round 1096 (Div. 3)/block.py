import sys
d = sys.stdin.read().split()
if d:
    o = []
    k = 1
    while k < len(d):
        n = int(d[k])
        a = [int(x) for x in d[k+1:k+1+n]]
        s = [n + 1] * n
        for i in range(n - 2, -1, -1):
            s[i] = a[i+1] if a[i+1] < s[i+1] else s[i+1]
        b = sum([a[i] - s[i] for i in range(n) if a[i] > s[i]])
        p = [0] * (n + 2)
        for i in range(n):
            p[a[i]] = i + 1
        r = [0] * (n + 2)
        for i in range(1, n + 2):
            r[i] = r[i-1] if r[i-1] > p[i-1] else p[i-1]
        m = max([0] + [i - r[a[i]] for i in range(n) if i + 1 > r[a[i]]])
        o.append(str(b + m))
        k += n + 1
    sys.stdout.write('\n'.join(o) + '\n')
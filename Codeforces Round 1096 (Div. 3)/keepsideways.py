import sys
d = sys.stdin.read().split()
if d:
    r = []
    i = 1
    while i < len(d):
        n = int(d[i])
        a = [int(x) for x in d[i+1:i+n+1]]
        b = sorted(a)
        s = sum([(j + 1) * (b[j] - a[j]) for j in range(n)])
        f = {}
        for j in range(n):
            if b[j] not in f:
                f[b[j]] = j + 1
        m = max([0] + [k + 1 - f[a[k]] for k in range(n)])
        r.append(str(s + m))
        i += n + 1
    sys.stdout.write('\n'.join(r) + '\n')
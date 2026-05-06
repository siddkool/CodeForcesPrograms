import sys
d = sys.stdin.read().split()
if d:
    o = []
    i = 1
    l = len(d)
    while i < l:
        n = int(d[i])
        p = [0] * (n + 1)
        for j in range(n):
            p[j+1] = p[j] + (int(d[i+1+j]) if j % 2 == 0 else -int(d[i+1+j]))
        u = sorted(set(p))
        z = len(u)
        m = {v: k + 1 for k, v in enumerate(u)}
        e = [0] * (z + 1)
        w = [0] * (z + 1)
        s = 0
        for j in range(n + 1):
            r = m[p[j]]
            if j % 2 == 0:
                x = z
                v = 0
                while x > 0:
                    v += w[x]
                    x -= x & -x
                x = r
                y = 0
                while x > 0:
                    y += w[x]
                    x -= x & -x
                s += v - y
                x = r
                while x <= z:
                    e[x] += 1
                    x += x & -x
            else:
                x = r - 1
                v = 0
                while x > 0:
                    v += e[x]
                    x -= x & -x
                s += v
                x = r
                while x <= z:
                    w[x] += 1
                    x += x & -x
        o.append(str(s))
        i += n + 1
    sys.stdout.write('\n'.join(o) + '\n')
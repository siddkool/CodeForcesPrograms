import sys

def f():
    r = sys.stdin.read().split()
    if not r: return
    t = int(r[0])
    p = 1
    o = []
    for _ in range(t):
        a = r[p]
        n = int(r[p+1])
        d = r[p+2:p+2+n]
        p += 2 + n
        l = len(a)
        c = []
        x = d[0]
        y = d[-1]
        if l > 1:
            c.append(int(y * (l - 1)))
        if y != '0':
            z = next((k for k in d if k != '0'), x)
            c.append(int(z + x * l))
        else:
            c.append(0)
        m = True
        s = ""
        for i in range(l):
            v = a[i]
            u = [k for k in d if k < v]
            if u and m:
                c.append(int(s + u[-1] + y * (l - 1 - i)))
            w = [k for k in d if k > v]
            if w and m:
                c.append(int(s + w[0] + x * (l - 1 - i)))
            if v in d:
                s += v
            else:
                m = False
                break
        if m:
            c.append(int(s))
        v = int(a)
        q = min(abs(v - e) for e in c)
        o.append(str(q))
    sys.stdout.write('\n'.join(o) + '\n')

f()

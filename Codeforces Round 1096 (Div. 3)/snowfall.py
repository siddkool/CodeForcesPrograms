import sys
d = sys.stdin.read().split()
if d:
    r = []
    i = 1
    while i < len(d):
        n = int(d[i])
        m, w, o, t = [], [], [], []
        for x in d[i+1:i+1+n]:
            v = int(x)
            if v % 6 == 0:
                m.append(x)
            elif v % 2 == 0:
                w.append(x)
            elif v % 3 == 0:
                t.append(x)
            else:
                o.append(x)
        r.append(" ".join(m + w + o + t))
        i += n + 1
    sys.stdout.write("\n".join(r) + "\n")
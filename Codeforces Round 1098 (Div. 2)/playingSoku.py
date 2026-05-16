import sys
r = sys.stdin.read().split()
if r:
    t = int(r[0])
    p = 1
    outcome = []
    for i in range(t):
        n = int(r[p])
        x = int(r[p+1])
        y = int(r[p+2])
        k = int(r[p+3])
        p += 4
        m = abs(x - y)
        d = min(m, n - m)
        if n < 4:
            outcome.append(str(d))
        else:
            outcome.append(str(d + k))
    sys.stdout.write('\n'.join(outcome) + '\n')

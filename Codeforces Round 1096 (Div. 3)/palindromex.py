import sys
d = sys.stdin.read().split()
if d:
    o = []
    i = 1
    while i < len(d):
        n = int(d[i]) * 2
        a = [int(c) for c in d[i+1:i+1+n]]
        p, q = [j for j in range(n) if a[j] == 0]
        def f(l, r):
            while l >= 0 and r < n and a[l] == a[r]:
                l -= 1
                r += 1
            s = set(a[l+1:r])
            x = 0
            while x in s:
                x += 1
            return x
        o.append(str(max(f(p, p), f(q, q), f((p+q)//2, (p+q+1)//2))))
        i += n + 1
    sys.stdout.write('\n'.join(o) + '\n')
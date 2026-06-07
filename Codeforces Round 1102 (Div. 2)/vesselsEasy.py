import sys

def solve():
    data = sys.stdin.read().split()
    if not data: return

    i = iter(map(int, data))
    t = next(i)

    out = []
    for _ in range(t):
        n = next(i)
        h = [next(i) for _ in range(n)]
        H = h + h

        # do array allocation OUTSIDE the loop to save memory overhead
        L = [0] * n
        R = [0] * n
        ans = []

        for j in range(n):
            m = 0
            for k in range(1, n):
                if H[j + k - 1] > m: m = H[j + k - 1]
                L[k] = m

            m = 0
            for k in range(n - 1, -1, -1):
                if H[j + k] > m: m = H[j + k]
                R[k] = m

            tot = sum(L[k] if L[k] < R[k] else R[k] for k in range(n))
            ans.append(str(tot))

        out.append(" ".join(ans))

    sys.stdout.write('\n'.join(out) + '\n')

solve()

import sys
i = iter(map(int, sys.stdin.read().split()))
next(i, None)
for n in i:
    a = sorted([next(i) for _ in range(n)])[::-1]
    print(f"{a[0]} {a[1]}" if all(x % y == z for x, y, z in zip(a, a[1:], a[2:])) else -1)

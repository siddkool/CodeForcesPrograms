t = int(input())

for i in range(t):
    n = int(input())
    w = list(map(int, input().split()))

    c0 = 0
    c1 = 0
    c2 = 0

    for j in range(n):
        if w[j] == 0:
            c0 += 1
        elif w[j] == 1:
            c1 += 1
        elif w[j] == 2:
            c2 += 1

    p = min(c1, c2)
    ans = c0 + p + ((c1 - p) // 3) + ((c2 - p) // 3)

    print(ans)

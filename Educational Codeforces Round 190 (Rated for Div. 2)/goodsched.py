import sys
from bisect import bisect_left

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    multTestQ = int(input_data[0])
    idx = 1
    out = []

    for _ in range(multTestQ):
        n = int(input_data[idx])
        idx += 1

        A = input_data[idx : idx+n]
        idx += n
        B = input_data[idx : idx+n]
        idx += n

        posA = [[] for _ in range(n + 2)]
        posB = [[] for _ in range(n + 2)]

        M = []
        A_int = [0] * (n + 1)
        B_int = [0] * (n + 1)

        for i in range(n):
            va = int(A[i])
            vb = int(B[i])
            A_int[i+1] = va
            B_int[i+1] = vb
            posA[va].append(i + 1)
            posB[vb].append(i + 1)
            if va == vb:
                M.append(i + 1)

        fail_after = [n + 1] * (n + 2)

        for j in reversed(M):
            k = A_int[j]
            nxt_k = k + 1

            listA = posA[nxt_k]
            idxA = bisect_left(listA, j + 1)
            if idxA < len(listA):
                nA = listA[idxA]
            else:
                nA = n + 1

            listB = posB[nxt_k]
            idxB = bisect_left(listB, j + 1)
            if idxB < len(listB):
                nB = listB[idxB]
            else:
                nB = n + 1

            if nA == n + 1 and nB == n + 1:
                fail_after[j] = n + 1
            elif nA != nB:
                fail_after[j] = min(nA, nB)
            else:
                fail_after[j] = fail_after[nA]

        ans = 0
        listA1 = posA[1]
        listB1 = posB[1]

        for L in range(1, n + 1):
            idxA = bisect_left(listA1, L)
            if idxA < len(listA1):
                nA = listA1[idxA]
            else:
                nA = n + 1

            idxB = bisect_left(listB1, L)
            if idxB < len(listB1):
                nB = listB1[idxB]
            else:
                nB = n + 1

            if nA == n + 1 and nB == n + 1:
                F = n + 1
            elif nA != nB:
                F = min(nA, nB)
            else:
                F = fail_after[nA]

            ans += (F - L)

        out.append(str(ans))

    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()

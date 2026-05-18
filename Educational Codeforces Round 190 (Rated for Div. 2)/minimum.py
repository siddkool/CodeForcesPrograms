import sys
from bisect import bisect_left

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    p = [int(x) for x in input_data[1:n+1]]
    c = [int(x) for x in input_data[n+1:2*n+1]]

    m = int(input_data[2*n+1])
    start_idx = 2*n+2
    tp = [int(x) for x in input_data[start_idx:start_idx+m]]
    tc = [int(x) for x in input_data[start_idx+m:start_idx+2*m]]
    d = [int(x) for x in input_data[start_idx+2*m:start_idx+3*m]]

    P_min_all = min(p)
    C_min_all = min(c)
    S_min_all = min(p[i] + c[i] for i in range(n))

    items_by_p = sorted(zip(p, c), key=lambda x: x[0])
    p_keys = [x[0] for x in items_by_p]
    pref_c = [0] * n
    pref_c[0] = items_by_p[0][1]
    for i in range(1, n):
        v = items_by_p[i][1]
        pref_c[i] = pref_c[i-1] if pref_c[i-1] < v else v

    items_by_c = sorted(zip(c, p), key=lambda x: x[0])
    c_keys = [x[0] for x in items_by_c]
    pref_p = [0] * n
    pref_p[0] = items_by_c[0][1]
    for i in range(1, n):
        v = items_by_c[i][1]
        pref_p[i] = pref_p[i-1] if pref_p[i-1] < v else v

    out = []
    inf = float('inf')

    for tpi, tci, di in zip(tp, tc, d):
        idx_p = bisect_left(p_keys, tpi) - 1
        if idx_p >= 0:
            c_star = pref_c[idx_p]
            if c_star < tci:
                out.append("0")
                continue
            C1 = c_star if c_star < tci + di else tci + di
        else:
            C1 = inf

        idx_c = bisect_left(c_keys, tci) - 1
        if idx_c >= 0:
            p_star = pref_p[idx_c]
            if p_star < tpi:
                out.append("0")
                continue
            C2 = p_star if p_star < tpi + di else tpi + di
        else:
            C2 = inf

        C3 = S_min_all
        v = P_min_all + tci + di
        if v < C3: C3 = v
        v = C_min_all + tpi + di
        if v < C3: C3 = v
        v = tpi + tci + di + di
        if v < C3: C3 = v

        ans = C1 if C1 < C2 else C2
        if C3 < ans: ans = C3

        out.append(str(ans))

    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()

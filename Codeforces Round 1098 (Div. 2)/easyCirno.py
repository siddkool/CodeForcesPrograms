import sys

def solve():
    r = sys.stdin.read().split()
    if not r: return
    t = int(r[0])
    p = 1
    o = []



    for _ in range(t):
        a = r[p]
        x = r[p+2]
        y = r[p+3]
        p += 4

        l = len(a)
        c = []


        if l > 1:
            c.append(int(y * (l - 1)))


        z = y if x == '0' else x
        c.append(int(z + x * l))

#

        def dfs(idx, state, cur): #no shot this works lol
            if idx == l:
                c.append(int(cur))
                return
            if state == 1:
                dfs(idx+1, 1, cur + y)
            elif state == 2:
                dfs(idx+1, 2, cur + x)
            else:
                for k in (x, y):
                    if k < a[idx]:
                        dfs(idx+1, 1, cur + k)
                    elif k > a[idx]:
                        dfs(idx+1, 2, cur + k)
                    else:
                        dfs(idx+1, 0, cur + k)

        dfs(0, 0, "")

        v = int(a)
        ans = min(abs(v - w) for w in c)
        o.append(str(ans))

    sys.stdout.write('\n'.join(o) + '\n')

solve()

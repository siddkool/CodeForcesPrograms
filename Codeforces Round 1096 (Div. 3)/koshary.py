import sys
d = sys.stdin.read().split()
for i in range(1, len(d), 2):
    print("NO" if int(d[i]) % 2 and int(d[i+1]) % 2 else "YES")
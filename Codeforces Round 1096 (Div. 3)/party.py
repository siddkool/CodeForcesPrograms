import sys
s = sys.stdin.read().split()
for i in range(2, len(s), 2):
    print("YES" if s[i].count('(') == s[i].count(')') else "NO")
import sys

inputs = sys.stdin.read().split()[1:]
array = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 22, 11]

for string in inputs:
    n = int(string)
    a = array[n % 12]
    print(f"{a} {n - a}" if a <= n else "-1")

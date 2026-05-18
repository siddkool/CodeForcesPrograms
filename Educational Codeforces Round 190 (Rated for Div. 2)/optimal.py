import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    t = int(input_data[0])
    results = []

    for i in range(1, 3 * t, 3):
        n = int(input_data[i])
        a = int(input_data[i+1])
        b = int(input_data[i+2])

        cost1 = n * a
        cost2 = (n // 3) * b + min((n % 3) * a, b)

        results.append(str(min(cost1, cost2)))

    sys.stdout.write('\n'.join(results) + '\n')

if __name__ == '__main__':
    solve()

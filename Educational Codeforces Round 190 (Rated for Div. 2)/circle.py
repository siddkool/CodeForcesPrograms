import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    t = int(input_data[0])
    results = []

    for i in range(1, t + 1):
        s = input_data[i]
        total_13 = s.count('1') + s.count('3')

        max_len = total_13
        current_2 = 0
        current_13 = 0

        for ch in s:
            if ch == '2':
                current_2 += 1
            elif ch == '1' or ch == '3':
                current_13 += 1

            current_len = current_2 + total_13 - current_13
            if current_len > max_len:
                max_len = current_len

        results.append(str(len(s) - max_len))

    sys.stdout.write('\n'.join(results) + '\n')

if __name__ == '__main__':
    solve()

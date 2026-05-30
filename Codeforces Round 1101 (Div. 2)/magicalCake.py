import sys

def process():
    data = sys.stdin.read().split()
    if not data:
        return

    index = 1
    tests = int(data[0])
    output = []

    for _ in range(tests):
        length = int(data[index])
        index += 1

        reqs = [0] * length
        for iterator in range(length):
            reqs[iterator] = int(data[index])
            index += 1

        places = [1] * (length + 1)
        steps = []
        valid = [True]

        def solve(layer, goals):
            if not valid[0]:
                return

            target = -1
            for level in range(layer, 0, -1):
                if places[level] != goals[level]:
                    target = level
                    break

            if target == -1:
                return

            source = places[target]
            dest = goals[target]
            spare = 6 - source - dest

            count = target - 1 - reqs[target - 1]

            if count < 0:
                valid[0] = False
                return

            subgoals = [0] + [spare] * count + [source] * (target - 1 - count)

            solve(target - 1, subgoals)
            if not valid[0]:
                return

            steps.append(str(target) + " " + str(source) + " " + str(dest))
            places[target] = dest

            solve(target - 1, goals)

        solve(length, [0] + [3] * length)

        if not valid[0]:
            output.append("NO")
        else:
            output.append("YES")
            output.append(str(len(steps)))
            output.extend(steps)

    sys.stdout.write("\n".join(output) + "\n")

process()

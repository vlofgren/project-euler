#!/usr/bin/python

digits = [ 1, 2, 3, 4 ]

def combine(digit, rest):
    if (len(rest) == 0):
        return [digit, -digit]
    fwd_combinations = combine(rest[0], rest[1:])
    combinations = set()

    for num in fwd_combinations:
        if num != 0:
            combinations.add(digit / float(num))
            combinations.add(-digit / float(num))
        combinations.add(digit * num)
        combinations.add(-digit * num)
        combinations.add(digit + num)
        combinations.add(-digit + num)

    return combinations

# There's more elegant ways of generating permutations :P

def permutations(values):
    if len(values) == 0:
        return []

    res = []
    for i in range(0, len(values)):
        after = permutations(values[0:i] + values[i+1:])
        if (len(after) == 0):
            res.append([values[i]])
        else:
            for perm in after:
                res.append([values[i]] + perm)

    return res

record = 0
for i in range(0,10):
    for j in range(0,10):
        for k in range(0,10):
            for l in range(0,10):
                results = set()
                for perm in permutations([i,j,k,l]):
                    for result in combine(perm[0], perm[1:]):
                        if abs(round(result) - result) < 1E-5:
                            results.add(int(result))
                consec = 0
                for p in range (0, len(results)):
                    if not p in results:
                        consec = p
                        break

                if record < consec:
                    record = consec
                    print [i,j,k,l], consec, results


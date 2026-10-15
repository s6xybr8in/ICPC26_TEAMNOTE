import sys

it = iter(map(int, sys.stdin.buffer.read().split()))
n, q = next(it), next(it)
a = [0] + [next(it) for _ in range(n)]
for _ in range(q):
    l, r = next(it), next(it)
    print(sum(a[i] for i in range(l, r + 1)))

import random
import sys

# stress.py passes a reproducible seed as argv[1].
rng = random.Random(int(sys.argv[1]))
n, q = rng.randint(1, 20), rng.randint(1, 30)
print(n, q)
print(*(rng.randint(-100, 100) for _ in range(n)))
for _ in range(q):
    l = rng.randint(1, n)
    r = rng.randint(l, n)
    print(l, r)  # 1-based closed interval [l, r]

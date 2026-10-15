"""
 * Author: Green Siro
 * License: CC0
 * Description: Windows stress test. Run: python stress.py
 * Put the three source files in the working directory.
"""

import subprocess as sp
import sys

GEN = "random_input.py"
NAIVE = "naive.py"  # Change to naive.cpp if needed.
TARGET = "target_file.cpp"
START, TESTS, TIME = 1, 1000, 2  # First seed, cases, seconds.


def build(name):
    if name.endswith(".py"):
        return [sys.executable, name]
    exe = name[:-4] + ".exe"
    sp.run(["g++", "-std=c++17", "-O2", name, "-o", exe], check=True)
    return [".\\" + exe]


def run(cmd, source, dest):
    with open(source, "rb") as inp, open(dest, "wb") as out:
        sp.run(cmd, stdin=inp, stdout=out, timeout=TIME, check=True)


gen, naive, target = build(GEN), build(NAIVE), build(TARGET)
for seed in range(START, START + TESTS):
    with open("seed.txt", "w") as f:
        f.write(str(seed))
    for name in ["naive.out", "target.out"]:
        open(name, "wb").close()
    try:
        with open("input.txt", "wb") as f:
            sp.run(gen + [str(seed)], stdout=f, timeout=TIME, check=True)
        run(naive, "input.txt", "naive.out")
        run(target, "input.txt", "target.out")
    except (sp.TimeoutExpired, sp.CalledProcessError) as e:
        print("ERROR, seed =", seed, e)
        sys.exit(1)
    with open("naive.out", "rb") as a:
        with open("target.out", "rb") as b:
            same = a.read().split() == b.read().split()
    if not same:
        print("WA, seed =", seed)
        print("See input.txt, naive.out, target.out")
        sys.exit(1)
    if (seed - START + 1) % 100 == 0:
        print("OK:", seed - START + 1, flush=True)
print("PASS:", TESTS)

#! /usr/bin/env python

import subprocess
import random
import os
import matplotlib.pyplot as plt


def relocate(limit):
    seed = int(random.random() * 100000)
    arg1 = f"-s {seed}"
    arg2 = "-n 1000"
    arg3 = f"-l {limit}"
    arg4 = "-c"
    result = subprocess.run(
    ["python", "relocation.py", arg1, arg2, arg3, arg4],
    capture_output=True,                    
    text=True                               
    )
    valid_count = 0
    for x in result.stdout.splitlines()[11:-1]:
        if "VALID" in x:
            valid_count += 1
    return valid_count

data = []
limits = []

for i in range(0, 1024, 10):
    limits.append(i)
    data.append(relocate(i) / 100.)

plt.plot(limits, data)
plt.xlabel("limit (-l)")
plt.ylabel("valid %")
plt.savefig("myPlot1.png")




#! /usr/bin/env python

import random

def aufgabe1():
    accessList = [random.randint(0, 9) for _ in range(10_000)]

    print(",".join(map(str, accessList)))

def distinct(a):
    return list(set(a))

def aufgabe2():
    acc = []

    for _ in range(10_000):
        if len(acc) < 5 or random.random() > 0.6:
            acc.append(random.randint(0, 9))
        else:
            acc.append(random.choice(distinct(acc[-5:])))
    print(",".join(map(str, acc)))


def aufgabe3():
    PAGE_SIZE = 4096
    acc = []
    with open('trace_output.txt', 'r') as trace_file:
        for line in trace_file:
            # Split the line into operation and memory address parts
            parts = line.strip().split()
            if len(parts) >= 2:
                operation = parts[0]
                address_info = parts[1]
                address = int(address_info.split(',')[0], 16)
                
                page_number = address >> 12
                acc.append(str(page_number))
    print(",".join(acc))

aufgabe3()
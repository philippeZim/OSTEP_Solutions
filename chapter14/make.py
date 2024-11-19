#! /usr/bin/env python

import os
import re
import subprocess

flags = "-g -Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wsign-conversion -O2"

c_files = [f for f in os.listdir() if f.endswith('.c')]#

commands = ["rm -f " + f[:-2] for f in c_files]

con = dict()


for x in c_files:
    with open(x, "r") as f:
        lines = f.read().splitlines()
    
    for z in lines:
        for y in c_files:
            if y[:-2] + ".h\"" in z:
                con[x[:-2]] = con.get(x[:-2], []) + [y[:-2]]

singles = [x[:-2] for x in c_files if x[:-2] not in con]

print(singles)

print(con)



for x in singles:
    commands.append("gcc -o " + x + " " + x + ".c " + flags)

for x in con:
    if not (len(con[x]) == 1 and con[x][0] == x):
        commands.append("gcc -o " + x + " " + x + ".c " + ".c ".join(con[x]) + ".c " + flags)

for x in commands:
    print(x)





def execute_commands(cmd_list):
    for cmd in cmd_list:
        try:
            print(f"\nExecuting command: {cmd}")
            result = subprocess.run(cmd, shell=True, text=True, capture_output=True)
            
            if result.stdout:
                print(f"Output:\n{result.stdout}")
            if result.stderr:
                print(f"Error:\n{result.stderr}")
                
        except Exception as e:
            print(f"Failed to execute {cmd}: {str(e)}")

execute_commands(commands)
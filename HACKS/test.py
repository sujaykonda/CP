import subprocess
import time
import sys
import os
import random

a = subprocess.run('g++ ' + 'HACKS/asol.cpp' + ' -std=c++17 -o HACKS/a.out', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
b = subprocess.run('g++ ' + 'HACKS/bsol.cpp' + ' -std=c++17 -o HACKS/b.out', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

def genTC():
    n = int(3000)
    tc = str(n) + " " + str(random.randint(1, 12)) + '\n'
    last = [0] * n
    for i in range(n):
        newlast = []
        for j in range(n):
            rng = random.randint(1, 12)
            num = (rng - 9) if rng > 10 else 1
            if last[j] == 2 and num == 2:
                num = 1
            newlast.append(num)
            tc += str(num) + " "
        last = newlast
        tc += '\n'
    return tc

while True:
    tc = genTC()
    ares = subprocess.run('./HACKS/a.out', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, input=tc)
    bres = subprocess.run('./HACKS/b.out', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, input=tc)\

    if(ares.stdout.strip() != bres.stdout.strip()):
        print("FAILED")
        f = open("HACKS/FAILEDTEST.txt", 'w')
        f.write(tc)
        f.close()
        print(ares.stdout)
        print(bres.stdout)
        break
    print("SUCCESS")
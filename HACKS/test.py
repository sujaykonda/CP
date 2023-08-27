import subprocess
import time
import sys
import os
import random

a = subprocess.run('g++ ' + 'HACKS/asol.cpp' + ' -std=c++17 -o HACKS/a.out', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
b = subprocess.run('g++ ' + 'HACKS/bsol.cpp' + ' -std=c++17 -o HACKS/b.out', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

def genTC():
    n = int(3e5)
    tc = "1\n" + str(n) + '\n'
    l = list(range(1, n + 1))
    random.shuffle(l)
    for i in l:
        tc += str(i) + " "
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
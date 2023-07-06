import random
import math

MAXSQRT = 31623

def grundy(x):
    xsqrt = 0
    for i in range(MAXSQRT):
        if i * i > x:
            xsqrt = i - 1
            break
    
    for i in range(xsqrt, -1, -1):
        if i * i < x:
            x -= (x - i * i + i) // (i + 1) * (i + 1)
        if i * i == x:
            return i
    
    return 0

def game(a):
    g = 0
    for ai in a:
        g ^= grundy(ai)
    return g

gg = []
for i in range(40):
    gg.append(grundy(i))

g = [0] * 40
for i in range(1, 40):
    x = [False] * (math.floor(math.sqrt(i)) + 2)
    for j in range(1, math.floor(math.sqrt(i)) + 1):
        x[g[i - j]] = True
    while(x[g[i]]):
        g[i] += 1

print(gg == g)

G = 30
s = str(G) + '\n'
ans = 0
for g in range(G):
    n = random.randint(1, 100)
    losing = random.randint(0, 2) == 0
    s += str(n)
    if(losing):
        n -= 1
    a = []
    for i in range(n):
        new = random.randint(1, 1e9 - 1)
        a.append(new)
        s += ' ' + str(new)
    if(losing): 
        s += ' ' + str(game(a)**2)
    s += '\n'
    if(losing): 
        ans += 1 << g


with open("testcase.in", 'w') as file:
    file.write(s)

print(ans)
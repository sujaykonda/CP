mn = 2**278
triple = (0, 0, 0)
v1 = 1
for i in range(1, 278):
    v1 *= 2
    v1 %= 2023
    v2 = 1
    for j in range(1, 278):
        v2 *= 2
        v2 %= 2023
        v3 = 1
        for k in range(1, 278):
            v3 *= 2
            v3 %= 2023
            if((v1 + v2 + v3) % 2023 == 0):
                v = 2**i + 2**j + 2**k
                if(mn > v):
                    triple = (i, j, k)
                    mn = v
print(mn, triple)
    
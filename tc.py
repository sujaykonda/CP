n = 1000000
s = str(n) + '\n'
for i in range(n - 1):
    s += str(i % (n // 6) + 1) + ' '
print(s)
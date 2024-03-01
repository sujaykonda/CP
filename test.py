N = int(1e5)
M = N * (N + 1) // 2
MOD = int(1e9 + 7)
ans = 0
for i in range(1, N + 1):
    ans += pow(2, M - 1 - (N - i) * (i + 1) - i, MOD) * (pow(2, i + 1, MOD) - 2)
    ans %= MOD
print(ans)
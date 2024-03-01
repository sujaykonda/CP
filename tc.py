N = int(2**20)
tc = str(N) + "\n"
for i in range(1, N // 2 + 1):
    tc += f"1 1 524288 {i}\n"
for i in range(1, N // 2 + 1):
    tc += f"2 {i}\n"
print(tc)